#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "array2.h"
#include "image_io.h"

#include "scalarField.h"


class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(int nx, int ny, vec2 a, vec2 b);

    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
