#include "heightField.h"



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

HeightField::HeightField()
{

}

HeightField::HeightField(int nx, int ny, vec2 a, vec2 b) : ScalarField(nx,ny,a,b){}

void HeightField::save(){

    QString fileName("/home/etu/p1409693/workspace/GeoMod/save.obj");
        if (!fileName.isNull()){
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream monFlux(&file);

        /*string const nomFichier("/home/etu/p1409693/workspace/GeoMod/save.obj");
        ofstream monFlux(nomFichier.c_str());*/


            monFlux << "#Sauvegarde .obj"<<endl;
            int nbPoints = 0;
            for (int x=0; x<nx; x++ ){
                for (int y=0; y<ny; y++ ){
                    nbPoints++;
                   monFlux<<"v"<<nbPoints<< " " << x <<" "<<y<<" "<<z[index(x,y)]<<endl;
                }
            }
            nbPoints = 0;
            int nbFaces = 0;
            for (int x=0; x<nx-1; x++ ){
                for (int y=0; y<ny-1; y++ ){
                    nbPoints++;
                    nbFaces++;
                   monFlux<<"f"<<nbFaces<<" v"<<nbPoints<<" v"<<nbPoints+nx<<" v"<<nbPoints+1<<endl;
                }
            }
        }


}
