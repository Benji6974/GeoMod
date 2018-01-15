#ifndef SCALARFIELD_H
#define SCALARFIELD_H
#include "array2.h"
#include <QString>
#include <QPixmap>
#include <QCoreApplication>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <string>
#include <GL/gl.h>

class ScalarField: public Array2
{
public:
    ScalarField();
    ScalarField(int nx, int ny, vec2 a, vec2 b);
    int index(int i,int j);
    vec3 P(int i,int j);
    bool inside(int x,int y,int z);
    double height(const vec2& p);
    double heightGrid(int i,int j);
    vec2 getCellSize();
    double InterpolationBilineaire(const vec2& uv,double v00,double v01, double v10, double v11);
    void load(QString relativePathFileName, vec2 a, vec2  b, float za, float zb);
    QImage getImage();
    std::vector<vec3> tri();
    float pente(vec2 source, vec2 destination);
    void majVoisinEcoulement(vec3 pos, ScalarField sf);
    ScalarField ecoulement();
    vec2 calculMinMax();
    bool saveImg(QString s);
    void changeSizeZ();

    vec2 Gradiant(int i, int j);
    vec2 longueurE();




protected:
      QVector<double> z; //Array of height

};
#endif // SCALARFIELD_H
