#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "array2.h"
#include "image_io.h"
#include <string>


class HightField : public Array2
{
public:
    HightField();
    void load(std::string img,vec2 a, vec2 b,float za, float zb);

    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
