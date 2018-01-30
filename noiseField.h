#ifndef NOISEFIELD_H
#define NOISEFIELD_H

#include "scalarField.h"
#include <cmath>
#include <random>
#include <vector>
#include <cstdint>
#include <numeric>
#include <algorithm>

typedef struct Param
{
    Param() : octaves(1), frequence(1), amplitude(1),
        lacunarity(2), persistance(0.5)
    {}

    Param(int oct, double freq, double a, double lac, double pers) : octaves(oct), frequence(freq), amplitude(a),
        lacunarity(lac), persistance(pers)
    {}

    void setOctaves(int oct)
    {
        if(oct > 0)
            this->octaves = oct;
    }

    void setFrequence(double freq)
    {
        this->frequence = freq;
    }

    void setAmplitude(double a)
    {
        this->amplitude = a;
    }

    void setLacunarity(double lac)
    {
        this->lacunarity = lac;
    }

    void setPersistance(double pers)
    {
        this->persistance = pers;
    }

    int octaves;
    double frequence;
    double amplitude;
    double lacunarity;
    double persistance;
} Param;

class NoiseField: public ScalarField
{
public:
    NoiseField();
    NoiseField(int nx, int ny, vec2 a, vec2 b);
    double H(vec2 p);
    double sumPerlinNoise(vec2 point);
    void generate(int seed);

    Param parameters;
private:
    double noise(vec2 point);

    int seed;
    static int hash[512];
    static int hashMask;
    static vec2 gradients2D[8];
    static int gradientsMask2D;
};

#endif // NOISEFIELD_H
