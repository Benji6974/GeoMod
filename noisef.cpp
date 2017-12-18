#include "noisef.h"

NoiseF::NoiseF(NoiseFunction nFunction,vec2 a, vec2 b) : nF(nFunction),a(a),b(b) {
//choisir valeur par default poour l'amplitude et le lambda
}

double NoiseF::H(float x, float y)
{
    return nF(x,y,a,b);
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
//probleme : savoir ou declarer les fonction de noise
//si dans .h  ==> erreur multiple declaration
//si dans .cpp ==> introuvable par le compilateur

double testNoiseFunction(float x,float y,vec2 a, vec2 b)
{
    return cos(x) + sin(y);
}



