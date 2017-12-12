#ifndef LAYERFIELD_H
#define LAYERFIELD_H
#include "heightField.h"

class LayerField : public ScalarField
{
public:
    LayerField();
    void affiche();
    HeightField br; // couche bedrock
    HeightField sable; //couche de sable
    HeightField montagne; //couche montagne
    HeightField eau; // couche d'eau
private:

};

#endif // LAYERFIELD_H
