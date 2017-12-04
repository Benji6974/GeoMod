#ifndef LAYERFIELD_H
#define LAYERFIELD_H
#include "heightField.h"

class LayerField
{
public:
    LayerField();

private:
    HightField br; // couche bedrock
    HightField sable; //couche de sable
    HightField montagne; //couche montagne
    HightField eau; // couche d'eau
};

#endif // LAYERFIELD_H
