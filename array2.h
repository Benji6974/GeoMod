#ifndef ARRAY2_H
#define ARRAY2_H
#include "box2.h"

class Array2 : public Box2
{
public:
    Array2();
protected:
    int nx,ny; //Discretisation
};

#endif // ARRAY2_H
