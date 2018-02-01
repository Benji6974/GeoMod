#ifndef LAYERFIELD_H
#define LAYERFIELD_H
#include "heightField.h"

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
    void calculLumiere(int nbSrcLum, int nbPas);

    ScalarField slopeField;
    ScalarField drainageField;
    ScalarField wetnessField;
    ScalarField luxField;
private:


};

#endif // LAYERFIELD_H
