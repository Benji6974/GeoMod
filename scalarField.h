#ifndef SCALARFIELD_H
#define SCALARFIELD_H
#include "array2.h"
#include <QString>
#include <QPixmap>

class ScalarField: public Array2
{
public:
    ScalarField();
    ScalarField(int nx, int ny, vec2 a, vec2 b);
    int index(int i,int j);
    vec3 P(int i,int j);
    bool inside(int x,int y,int z);
    double height(const double& x, const double& y);
    double heightGrid(int i,int j);

    void load(QString img,vec2 a, vec2 b,float za, float zb);

protected:
    double z[]; //Array of height
};
#endif // SCALARFIELD_H
