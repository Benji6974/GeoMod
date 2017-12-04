#ifndef SCALARFIELD_H
#define SCALARFIELD_H
#include "vec.h"
#include <string>

class ScalarField
{
public:
    ScalarField();
    int index(int i,int j);
    vec3 P(int i,int j);
    bool inside(int x,int y,int z);
    double height(const double& x, const double& y);
    double heightGrid(int i,int j);

protected:
    Vector a,b; //Bounding box
    int nx,ny; //Discretisation
    double z[]; //Array of height
};
#endif // SCALARFIELD_H
