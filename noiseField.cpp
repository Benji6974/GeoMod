#include "noiseField.h"

using namespace std;

NoiseField::NoiseField(int nx, int ny, vec2 a, vec2 b): ScalarField(nx,ny,a,b)
{
    addParam(Param(1,1));
}

double NoiseField::H(vec2 p)
{
    return sumPerlinNoise(p.x,p.y);
}

void NoiseField::setParam(vector<Param> parameters)
{
    this->parameters = parameters;
}

void NoiseField::setParam(unsigned int index, Param p)
{
    if(index < this->parameters.size())
        this->parameters[index] = p;
}

void NoiseField::addParam(Param p)
{
    parameters.push_back(p);
}

void NoiseField::generate()
{
    for(int i = 0 ; i < nx ; i++)
    {
        for(int j = 0 ; j < ny ; j++)
        {
            //cout << "i= " << i << " j=" << j << endl;
            z[index(i,j)] = H(Vertex(i,j));

        }

    }
}

double rand_noise(int t)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distribution(0.0,255.0);

    return distribution(mt);
}


double linear_interpolate(double a, double b, double t)
{
    return (1. - t) * a + t * b;
}

double smooth_noise(double x,double y)
{
    //Partie entière : E(x)
    int integer_x = (int)x;
    int integer_y = (int)x;
    //Partie fractionnaire : x - E(x)
    double fractional_x = x - integer_x;
    double fractional_y = y - integer_y;


    //Bruit du point précédent :
    double a = rand_noise(integer_x);
    //Bruit du point suivant :
    double b = rand_noise(integer_x + 1);

    //Bruit du point précédent :
    double c = rand_noise(integer_y);
    //Bruit du point suivant :
    double d = rand_noise(integer_y + 1);

    //Interpolation :

    double f = linear_interpolate(a, b, fractional_x);
    double g = linear_interpolate(c, d, fractional_x);

    return linear_interpolate(f, g, fractional_y);
}

double NoiseField::sumPerlinNoise(double x, double y)
{

    double value = 0;
    for(unsigned int i = 0 ; i < parameters.size() ; i++)
    {
        value += parameters[i].amplitude * smooth_noise(x/parameters[i].lambda,y/parameters[i].lambda);
    }
    return value;
}





