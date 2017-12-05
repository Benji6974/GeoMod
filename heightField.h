#ifndef HIGHTFIELD_H
#define HIGHTFIELD_H
#include "array2.h"
#include "image_io.h"
#include <string>
#include "scalarField.h"
#include <QCoreApplication>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <GL/gl.h>


class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(int nx, int ny, vec2 a, vec2 b);
    void save();
    void affiche();
    void drawline(vec3 s1, vec3 s2, float color[3]);
    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
