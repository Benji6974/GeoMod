#include "heightField.h"



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

HeightField::HeightField()
{

}

HeightField::HeightField(int nx, int ny, vec2 a, vec2 b) : ScalarField(nx,ny,a,b){}



bool HeightField::save(QString pathFile){

    //QString pathFile = QDir::currentPath() + fileName;
    if (!pathFile.isNull()){
        QFile file(pathFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
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
    return true;
}

void HeightField::affiche(){


   for (int x=0; x<nx-1; x++ ){
       for (int y=0; y<ny-1; y++ ){
           float c1 = z[index(x,y)];
           float c2 = z[index(x,y+1)];
           float c3 = z[index(x+1,y+1)];
           float c4 = z[index(x+1,y)];

            c1 = c1/50;
            c2 = c2/50;
            c3 = c3/50;
            c4 = c4/50;

            float color1[3];
            color1[0] = 0;
            color1[1] = c1;
            color1[2] = 0.5;

            float color2[3];
            color2[0] = 0;
            color2[1] = c2;
            color2[2] = 0.5;

            float color3[3];
            color3[0] = 0;
            color3[1] = c3;
            color3[2] = 0.5;

            float color4[3];
            color4[0] = 0;
            color4[1] = c4;
            color4[2] = 0.5;

           vec3 p1 = P(x,y);
           vec3 p2 = P(x,y+1);
           vec3 p3 = P(x+1,y+1);
           vec3 p4 = P(x+1,y);
          drawline(p1,p2,color1);
          drawline(p2,p3,color2);
          drawline(p3,p1,color3);

          drawline(p1,p3,color1);
          drawline(p3,p4,color3);
          drawline(p4,p1,color4);
       }
   }

}

void HeightField::drawline(vec3 s1, vec3 s2, float color[3]) {
    glLineWidth(0.5);
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_LINES);
    float scale = 0.05;
    glVertex3f(s1.x*scale, s1.y*scale, s1.z*scale);
    glVertex3f(s2.x*scale, s2.y*scale, s2.z*scale);

    glEnd();
}

Vector HeightField::normalTriangle(vec3 s1, vec3 s2, vec3 s3){
   return Vector((s2.y-s1.y)*(s3.z-s1.z)-(s2.z-s2.z)*(s3.y-s1.y),(s2.z-s1.z)*(s3.x-s1.x) - (s2.x-s1.x)*(s3.z-s1.z),(s1.x-s1.x)*(s3.y-s1.y) - (s2.y-s1.y)*(s3.x-s1.x));
}

vec3 HeightField::normal(vec2 s1){

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


std::vector<vec3> HeightField::tri(){
    return ScalarField::tri();
}
