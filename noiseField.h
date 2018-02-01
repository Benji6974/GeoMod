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
    Param() : offset(vec2(0.f,0.f)), octaves(1), frequence(1.f), amplitude(1.f),
        lacunarity(2.f), persistance(0.5f)
    {}

    Param(vec2 pos, int oct, float freq, float a, float lac, float pers) : offset(pos), octaves(oct), frequence(freq), amplitude(a),
        lacunarity(lac), persistance(pers)
    {}

    void setOctaves(int oct)
    {
        if(oct > 0)
            this->octaves = oct;
    }

    void setFrequence(float freq)
    {
        this->frequence = freq;
    }

    void setAmplitude(float a)
    {
        this->amplitude = a;
    }

    void setLacunarity(float lac)
    {
        this->lacunarity = lac;
    }

    void setPersistance(float pers)
    {
        this->persistance = pers;
    }

    void setOffset(vec2 pos)
    {
        this->offset = pos;
    }

    vec2 offset;
    int octaves;
    float frequence;
    float amplitude;
    float lacunarity;
    float persistance;
} Param;

class NoiseField: public ScalarField
{
public:
    NoiseField();
    NoiseField(int nx, int ny, vec2 a, vec2 b);
    float sumPerlinNoise(vec2 point);
    void generate(int seed);

    Param parameters;
private:
    float perlinNoise(vec2 point);
    void regenerateHash(int s);

    int seed;
    std::vector<int> hash;
    static int hashMask;
    static vec2 gradients2D[8];
    static int gradientsMask2D;
    static float sqrt2;
};

#endif // NOISEFIELD_H
