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


class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(int nx, int ny, vec2 a, vec2 b);
    void save();

    // ajouter ici les fonctions de hauteur
};

#endif // HIGHTFIELD_H
