#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include "layerField.h"
#include <QMouseEvent>


class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();
    void update();

    virtual void resizeGL(int w, int h);
    LayerField *lf;
    std::string aff;
    float _scale;
protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    void drawSierpinski();
//    Gasket gasket;


    float _angleX;
    float _angleY;

    float _deplacementX;
    float _deplacementY;
    QPoint _position;

    
signals:
    
public slots:
    
};

#endif // GLDISPLAY_H
