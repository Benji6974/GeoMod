#include "noisef.h"

NoiseF::NoiseF(double (*noiseFunction)(float,float,vec2,vec2),vec2 a, vec2 b) : noiseFunction(noiseFunction),a(a),b(b) {
//choisir valeur par default poour l'amplitude et le lambda
}

double NoiseF::H(float x, float y)
{
    return noiseFunction(x,y,a,b);
}

void NoiseF::setAmplitude(double a[10])
{
    for(int i=0 ; i < 10 ; i++)
    {
        this->amplitude[i] = a[i];
    }
}

void NoiseF::setAmplitude(int index, double a)
{
    this->amplitude[index] = a;
}

void NoiseF::setLambda(double l[10])
{
    for(int i=0 ; i < 10 ; i++)
    {
        this->lambda[i] = l[i];
    }
}

void NoiseF::setLambda(int index, double l)
{
    this->lambda[index] = l;
}



