#include "box2.h"

Box2::Box2()
{

}

Box2::Box2(vec2 a, vec2 b){
    this->a = a;
    this->b = b;
}

vec2 Box2::getA(){
    return this->a;
}

vec2 Box2::getB(){
    return this->b;
}

void Box2::setA(vec2 n){
    this->b = n;
}

void Box2::setB(vec2 n){
    this->a = n;
}
