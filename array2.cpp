#include "array2.h"

Array2::Array2():Box2(0,0)
{
    this->nx = 0;
    this->ny = 0;
}


Array2::Array2(int nx, int ny, int a, int b): Box2(a,b){
    this->nx = nx;
    this->ny = ny;
}
