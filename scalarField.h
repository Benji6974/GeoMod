#ifndef SCALARFIELD_H
#define SCALARFIELD_H
#include "array2.h"
#include <string>

class ScalarField: public Array2
{
public:
    ScalarField();
    int index(int i,int j);
    vec3 P(int i,int j);
    bool inside(int x,int y,int z);
    double height(const double& x, const double& y);
    double heightGrid(int i,int j);

protected:
    double z[]; //Array of height
};
#endif // SCALARFIELD_H
