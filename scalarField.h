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
    void save(QString fileName);
    void affiche();
    void drawline(vec3 s1, vec3 s2, float color[3]);
    vec3 normal(vec2 s1);
    Vector normalTriangle(vec3 s1, vec3 s2, vec3 s3);
    void load(QString relativePathFileName, vec2 a, vec2  b, float za, float zb);
    QImage getImage();

    QVector<double> z; //Array of height

protected:

};
#endif // SCALARFIELD_H
