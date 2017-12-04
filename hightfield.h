#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "scalarfield.h"
#include "image_io.h"
#include <string>


class HightField : public ScalarField
{
public:
    HightField();
    void load(std::string img,vec2 a, vec2 b,float za, float zb);

    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
