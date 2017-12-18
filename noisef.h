#ifndef NOISEF_H
#define NOISEF_H

#include "vec.h"
#include <cmath>


double testNoiseFunction(float x,float y,vec2 a, vec2 b)
{
    return cos(x) + sin(y);
}

class NoiseF
{
public:
    NoiseF(double (*noiseFunction)(float,float,vec2,vec2),vec2 a, vec2 b);
    double H(float x, float y);
    void setAmplitude(double a[10]);
    void setAmplitude(int index, double a);
    void setLambda(double lambda[10]);
    void setLambda(int index, double lambda);

private:
    double amplitude[10];
    double lambda[10];
    double (*noiseFunction)(float,float,vec2,vec2);
    vec2 a;
    vec2 b;

};

#endif // NOISEF_H
