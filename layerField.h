#ifndef LAYERFIELD_H
#define LAYERFIELD_H
#include "heightField.h"

class LayerField : public ScalarField
{
public:
    LayerField();

private:
    HeightField br; // couche bedrock
    HeightField sable; //couche de sable
    HeightField montagne; //couche montagne
    HeightField eau; // couche d'eau
};

#endif // LAYERFIELD_H
