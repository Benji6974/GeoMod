#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "array2.h"
#include "image_io.h"

#include "scalarField.h"
#include <GL/gl.h>

class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(int nx, int ny, vec2 a, vec2 b);
    void save(QString fileName);
    void affiche();
    void drawline(vec3 s1, vec3 s2, float color[3]);
    vec3 normal(vec2 s1);
    Vector normalTriangle(vec3 s1, vec3 s2, vec3 s3);
    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
