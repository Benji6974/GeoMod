#ifndef ARRAY2_H
#define ARRAY2_H
#include "box2.h"

class Array2 : public Box2
{
public:
    Array2();
    Array2(int nx, int ny);
    Array2(int nx, int ny, vec2 a, vec2 b);
    vec2 getNxNy();
    void setNxNy(vec2 n);
protected:
    int nx,ny; //Discretisation
};

#endif // ARRAY2_H
