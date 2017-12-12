#include "scalarField.h"

#include <iostream>

ScalarField::ScalarField()
{
    z = QVector<double>();
}

ScalarField::ScalarField(int nx, int ny, vec2 a, vec2 b): Array2(nx,ny,a,b)
{
    z = QVector<double>(nx*ny);
}

int ScalarField::index(int i,int j){
    return i*ny+j;
}
vec3 ScalarField::P(int i,int j){
    vec3 res;
    res.x = a.x+((b.x-a.x)/(nx-1))*i ; // voir a quoi correspond ax,bx etc ...
    res.y = a.y+((b.y-a.y)/(ny-1))*j ;
    res.z = z[index(i,j)] ;
    return res;
}

double ScalarField::heightGrid(int i,int j){
    // chepa ce que ca fait
    return P(i,j).z;
}

bool ScalarField::inside(int x,int y,int z){
    vec3 zt = P(x,y);
    return z<zt.z; // test un peu pourri int vs vec3 ??
}

vec2 ScalarField::getCellSize()
{
    return vec2((b.x-a.x)/(nx-1),(b.y-a.y)/(ny-1));
}

double ScalarField::InterpolationBilineaire(const vec2& uv,double v00,double v01, double v10, double v11)
{
    return (1-uv.x)*(1-uv.y)*v00 +
            (1-uv.x)*uv.y*v01 +
            uv.x*(1-uv.y)*v10 +
            uv.x*uv.y*v11;
}

double ScalarField::height(const vec2& p){
    //interpolation bilineaire
    vec2 uv = (p-a)/(b-a);

    //location de la celulle sur la grille
    int nu=int(uv.x*(nx-1));
    int nv=int(uv.y*(ny-1));

    //coordonées locale sur la cellule
    vec3 pij = P(nu,nv);

    vec2 sizeC = getCellSize();
    uv = (p-vec2(pij.x,pij.y))/sizeC;


    return InterpolationBilineaire(uv,pij.z,heightGrid(nu,nv+1),
                                   heightGrid(nu+1,nv),
                                   heightGrid(nu+1,nv+1));
    /*
    int nu=int(uv.x*nx);
    int nv=int(uv.y*ny);

    vec3 q11 = P(nu,nv);
    vec3 q21 = P(nu+1,nv);
    vec3 q12 = P(nu,nv+1);
    vec3 q22 = P(nu+1,nv+1);

    float dx = p.x - q11.x;
    float dy = p.y - q11.y;
    float sigmaX = q22.x - q11.x;
    float sigmaY = q22.y - q11.y;

    double sigmaFx = q21.z - q11.z;
    double sigmaFy = q12.z - q11.z;
    double sigmaFxy = q11.z + q22.z - q21.z - q12.z;

    return sigmaFx*(dx/sigmaX)+sigmaFy*(dy/sigmaY)+sigmaFxy*(dx/sigmaX)*(dy/sigmaY)+q11.z;
    */
    //interpolation triangulaire (non fonctionelle)
    /*
    //coordonées locales
    double u=(x-a.x)/(b.x-a.x);
    double v=(y-a.y)/(b.y-a.y);

    //location de la celulle sur la grille
    int nu=int(u*nx);
    int nv=int(v*ny);

    //coordonées locale sur la cellule
    u=u-nu*(b.x-a.x)/nx;
    v=v-nv*(b.y-a.y)/ny;

    if(u+v<1){
        return (1-u-v)*heightGrid(nu,nv)+u*heightGrid(nu+1,nv)+v*heightGrid(nu,nv+1); // completement pourri son code y'a pas de i ni de j !!!
    }else{
        return (u+v-1)*heightGrid(nu+1,nv+1)+(1-v)*heightGrid(nu+1,nv)+(1-u)*heightGrid(nu,nv+1);
    }
    */
}



void ScalarField::load(QString pathFile, vec2 a, vec2  b, float za, float zb){

    this->a = a;
    this->b = b;

    //QString pathFile = QDir::currentPath() + relativePathFileName;
    QImage img(pathFile);

    if(img.isNull())
        return;

    img.scaled(nx,ny);

    for(int i = 0 ; i < this->nx ; i++)
    {
        for(int j = 0 ; j < this->ny ; j++)
        {
            int value =  qGray(img.pixel(i,j));
            double h = ((double)value/255.f)*(zb-za) + za;
            z[index(i,j)] = h;
        }
    }

    std::cout<<"Image lue"<<std::endl;

}

QImage ScalarField::getImage()
{
    QImage img;

    if(nx + ny < 1)
        return img;

    for(int i = 0 ; i < this->nx ; i++)
    {
        for(int j = 0 ; j < this->ny ; j++)
        {
            /*
            img.set
            int value =  qGray(img.pixel(i,j));
            double h = ((double)value/255.f)*(zb-za) + za;
            z[index(i,j)] = h;
            */
        }
    }
    return img;
}


void ScalarField::save(QString pathFile){

    //QString pathFile = QDir::currentPath() + fileName;
    if (!pathFile.isNull()){
        QFile file(pathFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream monFlux(&file);

        /*string const nomFichier("/home/etu/p1409693/workspace/GeoMod/save.obj");
        ofstream monFlux(nomFichier.c_str());*/


        monFlux << "#Sauvegarde .obj"<<endl;
        monFlux << "o objet"<<endl;

        for (int x=0; x<nx; x++ ){
            for (int y=0; y<ny; y++ ){
               vec3 res = P(x,y);
               vec3 resNormal = normal(vec2(x,y));
               monFlux<<"v"<< " " << res.x <<" "<<res.y<<" "<<res.z<<endl;
               monFlux<<"vn"<< " " << resNormal.x <<" "<<resNormal.y<<" "<<resNormal.z<<endl;
            }
        }
        int nbPoints = 0;
        monFlux <<endl;
        monFlux << "g faces"<<endl;
        for (int x=0; x<nx-1; x++ ){
            for (int y=0; y<ny-1; y++){
               nbPoints++;
               int num = (y+x*ny)+1;
               monFlux<<"f"<<" "<<num<<"//"<<num<<" "<<num+ny+1<<"//"<<num+ny+1<<" "<<num+ny<<"//"<<num+ny<<endl;
               monFlux<<"f"<<" "<<num<<"//"<<num<<" "<<num+1<<"//"<<num+1<<" "<<num+ny+1<<"//"<<num+ny+1<<endl;
            }
        }
    }

    std::cout << "heightField sauvegarder dans " + pathFile.toStdString() << std::endl;
}

void ScalarField::affiche(){

   float color[3];
   color[0] = 0;
   color[1] = 1;
   color[2] = 0;
   for (int x=0; x<nx-1; x++ ){
       for (int y=0; y<ny-1; y++ ){
           vec3 p1 = P(x,y);
           vec3 p2 = P(x,y+1);
           vec3 p3 = P(x+1,y+1);
           vec3 p4 = P(x+1,y);
          drawline(p1,p2,color);
          drawline(p2,p3,color);
          drawline(p3,p1,color);

          drawline(p1,p3,color);
          drawline(p3,p4,color);
          drawline(p4,p1,color);
       }
   }

}

void ScalarField::drawline(vec3 s1, vec3 s2, float color[3]) {
    glLineWidth(0.5);
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_LINES);
    float scale = 0.05;
    glVertex3f(s1.x*scale, s1.y*scale, s1.z*scale);
    glVertex3f(s2.x*scale, s2.y*scale, s2.z*scale);

    glEnd();
}

Vector ScalarField::normalTriangle(vec3 s1, vec3 s2, vec3 s3){
   return Vector((s2.y-s1.y)*(s3.z-s1.z)-(s2.z-s2.z)*(s3.y-s1.y),(s2.z-s1.z)*(s3.x-s1.x) - (s2.x-s1.x)*(s3.z-s1.z),(s1.x-s1.x)*(s3.y-s1.y) - (s2.y-s1.y)*(s3.x-s1.x));
}

vec3 ScalarField::normal(vec2 s1){

    if (s1.x == 0){
        if (s1.y == 0){ // cas en haut a gauche
            Vector qv3_1;
            Vector qv3_2;
            Vector qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x,s1.y+1);
            vec3 p3 = P(s1.x+1,s1.y+1);
            vec3 p4 = P(s1.x+1,s1.y);
            qv3_1 = normalTriangle(p1,p3,p4);
            qv3_2 = normalTriangle(p1,p2,p3);
            qv3_res = (qv3_1+qv3_2)/2;
            return vec3(normalize(qv3_res));
        }else if(s1.y == ny-1){ // cas en bas a gauche
            Vector qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x+1,s1.y);
            vec3 p3 = P(s1.x,s1.y-1);
            qv3_res = normalTriangle(p1,p2,p3);
            return vec3(normalize(qv3_res));
        }else{ // cas ligne gauche
            Vector qv3_1;
            Vector qv3_2;
            Vector qv3_3;
            Vector qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x,s1.y+1);
            vec3 p3 = P(s1.x+1,s1.y+1);
            vec3 p4 = P(s1.x+1,s1.y);
            vec3 p5 = P(s1.x,s1.y-1);
            qv3_1 = normalTriangle(p1,p2,p3);
            qv3_2 = normalTriangle(p1,p3,p4);
            qv3_3 = normalTriangle(p1,p4,p5);
            qv3_res = (qv3_1+qv3_2+qv3_3)/3;
            return vec3(normalize(qv3_res));
        }
    }else if (s1.x == nx-1){
        if (s1.y == 0){ // cas en haut a droite
            Vector qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x-1,s1.y);
            vec3 p3 = P(s1.x,s1.y-1);
            qv3_res = normalTriangle(p1,p2,p3);
            return vec3(normalize(qv3_res));
        }else if(s1.y == ny-1){ // cas en bas a gauche
            Vector qv3_1,qv3_2,qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x,s1.y-1);
            vec3 p3 = P(s1.x-1,s1.y-1);
            vec3 p4 = P(s1.x-1,s1.y);
            qv3_1 = normalTriangle(p1,p2,p3);
            qv3_2 = normalTriangle(p1,p3,p4);
            qv3_res = (qv3_1+qv3_2)/2;
            return vec3(normalize(qv3_res));
        }else{ // cas ligne droite
            Vector qv3_1;
            Vector qv3_2;
            Vector qv3_3;
            Vector qv3_res;
            vec3 p1 = P(s1.x,s1.y);
            vec3 p2 = P(s1.x,s1.y-1);
            vec3 p3 = P(s1.x-1,s1.y-1);
            vec3 p4 = P(s1.x-1,s1.y);
            vec3 p5 = P(s1.x,s1.y+1);
            qv3_1 = normalTriangle(p1,p2,p3);
            qv3_2 = normalTriangle(p1,p3,p4);
            qv3_3 = normalTriangle(p1,p4,p5);
            qv3_res = (qv3_1+qv3_2+qv3_3)/3;
            return vec3(normalize(qv3_res));
        }
    }else if(s1.y == 0){ // cas ligne haut
        Vector qv3_1;
        Vector qv3_2;
        Vector qv3_3;
        Vector qv3_res;
        vec3 p1 = P(s1.x,s1.y);
        vec3 p2 = P(s1.x-1,s1.y);
        vec3 p3 = P(s1.x,s1.y+1);
        vec3 p4 = P(s1.x+1,s1.y+1);
        vec3 p5 = P(s1.x+1,s1.y);
        qv3_1 = normalTriangle(p1,p2,p3);
        qv3_2 = normalTriangle(p1,p3,p4);
        qv3_3 = normalTriangle(p1,p4,p5);
        qv3_res = (qv3_1+qv3_2+qv3_3)/3;
        return vec3(normalize(qv3_res));
    }else if(s1.y == ny-1){ // cas ligne bas
        Vector qv3_1;
        Vector qv3_2;
        Vector qv3_3;
        Vector qv3_res;
        vec3 p1 = P(s1.x,s1.y);
        vec3 p2 = P(s1.x+1,s1.y);
        vec3 p3 = P(s1.x,s1.y-1);
        vec3 p4 = P(s1.x-1,s1.y-1);
        vec3 p5 = P(s1.x-1,s1.y);
        qv3_1 = normalTriangle(p1,p2,p3);
        qv3_2 = normalTriangle(p1,p3,p4);
        qv3_3 = normalTriangle(p1,p4,p5);
        qv3_res = (qv3_1+qv3_2+qv3_3)/3;
        return vec3(normalize(qv3_res));
    }else{ // cas global 6 triangles
        Vector qv3_1;
        Vector qv3_2;
        Vector qv3_3;
        Vector qv3_4;
        Vector qv3_5;
        Vector qv3_6;
        Vector qv3_res;
        vec3 p1 = P(s1.x,s1.y);
        vec3 p2 = P(s1.x,s1.y-1);
        vec3 p3 = P(s1.x-1,s1.y-1);
        vec3 p4 = P(s1.x-1,s1.y);
        vec3 p5 = P(s1.x,s1.y+1);
        vec3 p6 = P(s1.x+1,s1.y+1);
        vec3 p7 = P(s1.x+1,s1.y);
        qv3_1 = normalTriangle(p1,p2,p3);
        qv3_2 = normalTriangle(p1,p3,p4);
        qv3_3 = normalTriangle(p1,p4,p5);
        qv3_4 = normalTriangle(p1,p5,p6);
        qv3_5 = normalTriangle(p1,p6,p7);
        qv3_6 = normalTriangle(p1,p7,p2);
        qv3_res = (qv3_1+qv3_2+qv3_3+qv3_4+qv3_5+qv3_6)/6;
        return vec3(normalize(qv3_res));
    }
    return vec3(0,0,0);
}
