#ifndef NOISEFIELD_H
#define NOISEFIELD_H

#include "scalarField.h"
#include <cmath>

enum NOISE_TYPE
{
    TEST,
    PERLIN
};

class NoiseField: public ScalarField
{
public:
    NoiseField(int nx, int ny, vec2 a, vec2 b);
    double H(vec2 p);
    void setAmplitude(double a[10]);
    void setAmplitude(int index, double a);
    void setLambda(double lambda[10]);
    void setLambda(int index, double lambda);
    double testNoiseFunction(float x,float y,vec2 a, vec2 b);
    double perlinNoise(int octaves, double frequency,double persistence, double x);
    void generate();
private:
    double amplitude[10];
    double lambda[10];
};

#endif // NOISEFIELD_H
