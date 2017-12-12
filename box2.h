#ifndef BOX2_H
#define BOX2_H
#include "vec.h"

class Box2
{
public:
    Box2();
    Box2(vec2 a, vec2 b);
    vec2 getA();
    vec2 getB();
    void setA(vec2 n);
    void setB(vec2 n);
protected:
    vec2 a,b;
};

#endif // BOX2_H
