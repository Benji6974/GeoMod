#include "noiseField.h"

using namespace std;

NoiseField::NoiseField(): ScalarField()
{}

NoiseField::NoiseField(int nx, int ny, vec2 a, vec2 b): ScalarField(nx,ny,a,b)
{
    this->seed = 123;
    reseed(seed);
}

double NoiseField::H(vec2 p)
{
    return sumPerlinNoise(p.x,p.y);
}

void NoiseField::generate(int s)
{
    if(s != seed)
    {
        reseed(seed);
        seed = s;
    }

    for(int i = 0 ; i < nx ; i++)
    {
        for(int j = 0 ; j < ny ; j++)
        {
            //cout << "i= " << i << " j=" << j << endl;
            z[index(i,j)] = H(Vertex(i,j));

        }

    }
}

static double Fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static double Lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

static double Grad(std::int32_t hash, double x, double y, double z)
{
    const std::int32_t h = hash & 15;
    const double u = h < 8 ? x : y;
    const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void NoiseField::reseed(std::uint32_t seed)
{
    for (size_t i = 0; i < 256; i++)
    {
        p[i] = i;
    }

    std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

    for (size_t i = 0; i < 256; i++)
    {
        p[256 + i] = p[i];
    }
}

double NoiseField::noise(double x, double y, double z)
{
    const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
    const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
    const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    const double u = Fade(x);
    const double v = Fade(y);
    const double w = Fade(z);

    const std::int32_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    const std::int32_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z),
        Grad(p[BA], x - 1, y, z)),
        Lerp(u, Grad(p[AB], x, y - 1, z),
        Grad(p[BB], x - 1, y - 1, z))),
        Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),
        Grad(p[BA + 1], x - 1, y, z - 1)),
        Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1),
        Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double NoiseField::sumPerlinNoise(double x, double y)
{
    double sum = 0;
    double freq = parameters.frequence;
    double amp = parameters.amplitude;

    for (int i = 0 ; i < parameters.octaves ; i++) {
        sum += noise(x*freq, y*freq,0.0)*amp;

        freq *= parameters.lacunarity;
        amp *= parameters.persistance;
    }

    return sum;
}





