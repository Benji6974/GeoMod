#include "heightField.h"



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

HeightField::HeightField()
{

}

HeightField::HeightField(int nx, int ny, vec2 a, vec2 b) : ScalarField(nx,ny,a,b){}

void HeightField::save(QString fileName){

    QString pathFile = QDir::currentPath() + fileName;
    if (!pathFile.isNull()){
        QFile file(pathFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream monFlux(&file);

    /*string const nomFichier("/home/etu/p1409693/workspace/GeoMod/save.obj");
    ofstream monFlux(nomFichier.c_str());*/


        monFlux << "#Sauvegarde .obj"<<endl;
        monFlux << "o objet"<<endl;
        int nbPoints = 0;
        for (int x=0; x<nx; x++ ){
            for (int y=0; y<ny; y++ ){
                nbPoints++;
               monFlux<<"v"<< " " << x <<" "<<y<<" "<<z[index(x,y)]<<endl;
            }
        }
        nbPoints = 0;
        int nbFaces = 0;
        monFlux <<endl;
        monFlux << "g faces"<<endl;
        for (int x=0; x<nx-1; x++ ){
            for (int y=0; y<ny-1; y++ ){
                nbPoints++;
                nbFaces++;
               monFlux<<"f"<<" "<<nbPoints<<" "<<nbPoints+nx<<" "<<nbPoints+1<<endl;
            }
        }
    }

    cout << "heightField sauvegarder dans " + fileName.toStdString() << endl;
}

void HeightField::affiche(){

   float color[3];
   color[0] = 0;
   color[1] = 1;
   color[2] = 0;
   for (int x=0; x<nx; x++ ){
       for (int y=0; y<ny; y++ ){
          drawline(vec3(x,y,z[index(x,y)]),vec3(x+1,y,z[index(x+1,y)]),color);
          drawline(vec3(x+1,y,z[index(x+1,y)]),vec3(x,y+1,z[index(x,y+1)]),color);
          drawline(vec3(x,y+1,z[index(x,y+1)]),vec3(x,y,z[index(x,y)]),color);
       }
   }


}

void HeightField::drawline(vec3 s1, vec3 s2, float color[3]) {
    glLineWidth(0.5);
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_LINES);

    glVertex3f(s1.x, s1.y, s1.z);
    glVertex3f(s2.x, s2.y, s2.z);

    glEnd();
}
