#include "scalarField.h"

#include <iostream>
#include <algorithm>

ScalarField::ScalarField()
{
    z = QVector<double>();
}

ScalarField::ScalarField(int nx, int ny, vec2 a, vec2 b): Array2(nx,ny,a,b)
{
    z = QVector<double>(nx*ny);
}

void ScalarField::setAllZ(double val){
    for(int i = 0 ; i < this->nx ; i++)
    {
        for(int j = 0 ; j < this->ny ; j++)
        {
            z[index(i,j)] = val;
        }
    }
}

void ScalarField::changeSizeZ(){
    z.resize(getNxNy().x*getNxNy().y);
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
    QImage img = QImage(nx,ny,QImage::Format_RGB32);
    std::cout<<"debut gen image"<<std::endl;
    if(nx + ny < 1)
        return img;

     vec2 res = calculMinMax();
     std::cout<<"min:"<<res.x<<" max:"<<res.y<<std::endl;
     if (res.x == res.y){
         for(int i = 0 ; i < this->nx ; i++)
         {
             for(int j = 0 ; j < this->ny ; j++)
             {
                 QColor s;
                 s.setHsv(0,0,0);
                 img.setPixelColor(i,j,s);
             }
         }
     }else{
         for(int i = 0 ; i < this->nx ; i++)
         {
             for(int j = 0 ; j < this->ny ; j++)
             {
                 int color;
                 color = ((z[index(i,j)]-res.x)/(res.y-res.x))*255;
                 QColor s;
                 s.setHsv(0,0,color);
                 img.setPixelColor(i,j,s);
             }
         }
    }

    std::cout<<"fin gen image"<<std::endl;
    QTransform t;
    return img.transformed(t.rotate(-90));
}



std::vector<vec3> ScalarField::tri(){
    std::vector<vec3> v = std::vector<vec3>();
    std::cout<<this->nx<<std::endl;
    std::cout<<this->ny<<std::endl;
    for(int x = 0 ; x < this->nx ; x++){
        for(int y = 0 ; y < this->ny ; y++){
            v.push_back(vec3(x,y,z[index(x,y)]));
        }
    }

    std::sort(v.begin(), v.end(),TriDescendant());

    /*for (int i =0; i<v.size();i++){
        std::cout<<"z:"<<v[i].z<<" x:"<<v[i].x<<" y:"<<v[i].y<<std::endl;
    }*/

    return v;
}


float ScalarField::pente(vec2 source, vec2 destination){
    return z[index(destination.x, destination.y)] - z[index(source.x, source.y)];
}

vec2 ScalarField::Gradiant(int i, int j){
    vec2 dist = longueurE();
    float sx = (P(i+1,j).z - P(i-1,j).z) / (2*dist.x);
    float sy = (P(i,j+1).z - P(i,j-1).z) / (2*dist.y);
    return vec2(sx,sy);
}

vec2 ScalarField::longueurE()
{
    return vec2((b.x - a.x) / nx,(b.y - a.y) / ny);
}

vec2 ScalarField::calculMinMax(){
    float min = 999;
    float max = -999;
    for(int x = 0 ; x < this->nx ; x++){
        for(int y = 0 ; y < this->ny ; y++){
            if (z[index(x,y)] < min)
                min = z[index(x,y)];
            if (z[index(x,y)] > max)
                max = z[index(x,y)];
        }
    }
    return vec2(min, max);
}

bool ScalarField::saveImg(QString s){

        QString extension = QString(s[s.length()-3])+QString(s[s.length()-2])+QString(s[s.length()-1]);
        const char * extensionEnChar = extension.toStdString().c_str();
        QImage img = getImage();
        img.save(s, extensionEnChar);
        return true;
}



void ScalarField::setZ(int i,int j, double val){
    z[index(i,j)] = val;
}

double ScalarField::getZ(int i,int j){
    return z[index(i,j)];
}




