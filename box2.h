#ifndef BOX2_H
#define BOX2_H
#include "vec.h"

class Box2
{
public:
    Box2();
    Box2(vec2 a, vec2 b);
protected:
    vec2 a,b;
};

#endif // BOX2_H
