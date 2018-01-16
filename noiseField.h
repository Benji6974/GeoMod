#ifndef NOISEFIELD_H
#define NOISEFIELD_H

#include "scalarField.h"
#include <cmath>
#include <random>
#include <vector>

typedef struct Param
{
    Param(double l, double a) : lambda(l),amplitude(a)
    {}

    double lambda;
    double amplitude;
} Param;

class NoiseField: public ScalarField
{
public:
    NoiseField(int nx, int ny, vec2 a, vec2 b);
    double H(vec2 p);
    void setParam(std::vector<Param> parameters);
    void setParam(unsigned int index, Param p);
    void addParam(Param p);
    double sumPerlinNoise(double x, double y);
    void generate();
private:
    std::vector<Param> parameters;
};

#endif // NOISEFIELD_H
