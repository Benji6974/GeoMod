#include "array2.h"

Array2::Array2():Box2(0,0)
{
    this->nx = 0;
    this->ny = 0;
}


Array2::Array2(int nx, int ny, vec2 a, vec2 b): Box2(a,b){
    this->nx = nx;
    this->ny = ny;
}


vec2 Array2::getNxNy(){
    return vec2(this->nx,this->ny);
}

void Array2::setNxNy(vec2 n){
    this->nx = n.x;
    this->ny = n.y;
}

vec2 Array2::Vertex(int i, int j)
{
    vec2 res;
    res.x = a.x+((b.x-a.x)/(nx-1))*i ;
    res.y = a.y+((b.y-a.y)/(ny-1))*j ;
    return res;
}
