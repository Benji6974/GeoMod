#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "array2.h"
#include "image_io.h"
#include <string>


class HeightField : public Array2
{
public:
    HeightField();
    HeightField(int nx, int ny, vec2 a, vec2 b);
    void load(std::string img,vec2 a, vec2 b,float za, float zb);
    void save();

    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
