#include "noiseField.h"



NoiseField::NoiseField(int nx, int ny, vec2 a, vec2 b): ScalarField(nx,ny,a,b)
{
}

double NoiseField::H(vec2 p)
{
    return testNoiseFunction(p.x,p.y,a,b);
}

void NoiseField::setAmplitude(double a[10])
{
    for(int i=0 ; i < 10 ; i++)
    {
        this->amplitude[i] = a[i];
    }
}

void NoiseField::setAmplitude(int index, double a)
{
    this->amplitude[index] = a;
}

void NoiseField::setLambda(double l[10])
{
    for(int i=0 ; i < 10 ; i++)
    {
        this->lambda[i] = l[i];
    }
}

void NoiseField::setLambda(int index, double l)
{
    this->lambda[index] = l;
}

double NoiseField::testNoiseFunction(float x,float y,vec2 a, vec2 b)
{
    return cos(x) + sin(y);
}

void NoiseField::generate()
{
    for(int i = 0 ; i < nx ; i++)
    {
        for(int j = 0 ; j < ny ; j++)
        {
            std::cout << "i= " << i << " j=" << j << std::endl;
            z[index(i,j)] = H(Vertex(i,j));

        }

    }
}


double NoiseField::perlinNoise(int octaves, double frequency,
        double persistence, double x)
{

    double r = 0.;
    double f = frequency;
    double amplitude = 1.;

    for(int i = 0; i < octaves; i++)
    {
        r += smooth_noise(x * f) * amplitude;
        amplitude *= persistence;
        f *= 2;
    }

    double geo_lim = (1 - persistence) / (1 - amplitude);

    return r * geo_lim;
}





