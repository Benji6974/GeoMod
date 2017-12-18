#ifndef NOISEF_H
#define NOISEF_H

#include "vec.h"
#include <cmath>

typedef double (*NoiseFunction)(float,float,vec2,vec2);

double testNoiseFunction(float x,float y,vec2 a, vec2 b);

class NoiseF
{
public:
    NoiseF(NoiseFunction nFunction,vec2 a, vec2 b);
    double H(float x, float y);
    void setAmplitude(double a[10]);
    void setAmplitude(int index, double a);
    void setLambda(double lambda[10]);
    void setLambda(int index, double lambda);

private:
    double amplitude[10];
    double lambda[10];
    NoiseFunction nF;
    vec2 a;
    vec2 b;

};

#endif // NOISEF_H
