#ifndef LAYERFIELD_H
#define LAYERFIELD_H
#include "heightField.h"
#include "include/thinks/poissonDiskSampling.hpp"

#include <deque>
#include <random>
#include <cmath>

class LayerField;

template <typename T, std::size_t N>
class Vec
{
public:
  typedef T value_type;
  static const std::size_t size = N;
  Vec() {}
  T& operator[](std::size_t i) { return _data[i]; }
  const T& operator[](std::size_t i) const { return _data[i]; }
private:
  T _data[N];
};

typedef Vec<double, 2> Vec2f;



class tree{
public:
    tree(std::string type,vec2 h, vec2 hum, vec2 l, vec2 p, vec2 s, double r):type(type),hauteur(h),humidite(hum),lumiere(l),pente(p),streampower(s),radius(r){}

    std::string type;
    vec2 hauteur;
    vec2 humidite;
    vec2 lumiere;
    vec2 pente;
    vec2 streampower;
    double radius;
};


class Veget
{
public:
    Veget();
    //void seLayerField(LayerField *lf);
    std::vector<tree> arbres;
    double fcntTransfert(vec2 val, double test);
    void poisson(LayerField &a);
    void afficheArbres();
    QImage getImageArbres(LayerField &lf);

    std::vector<vec3> arbresPlantee;
};


class LayerField : public HeightField
{
public:
    LayerField();
    LayerField(int nx, int ny, vec2 a, vec2 b);
    void affiche(std::string str);
    void affiche();
    HeightField br; // couche bedrock
    HeightField sable; //couche de sable
    HeightField montagne; //couche montagne
    HeightField eau; // couche d'eau
    std::vector<HeightField*> vec_HF;
    void heightTotal();
    void changeNxNy(vec2 n);
    void changeAB(vec2 a, vec2 b);
    std::vector<vec3> tri();
    void ecoulement();
    void majVoisinEcoulement(vec3 pos);
    double slope(int i, int j);
    void calculSlope();
    void calculWetness(float param);

    void calculErosion();
    void stabilization();
    void calculLumiere(int nbSrcLum, int nbPas);
    void calculPowerStream();
    void calculPoisson();
    QImage getImageArbres();

    Veget vegetation;

    ScalarField slopeField;
    ScalarField drainageField;
    ScalarField wetnessField;
    ScalarField luxField;
    ScalarField streamPower;

private:
    double getTanAngle(int x1, int y1, int x2, int y2);
    void ecoulementVoisin(std::deque<vec2i> & haveToUpdate, int x , int y, double angleMax);

};




#endif // LAYERFIELD_H
