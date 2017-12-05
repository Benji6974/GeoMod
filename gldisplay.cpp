#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f)
{
}

void GLDisplay::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(_angle, 0.0f, 1.0f, 0.0f);

//    gasket.draw();
    //maillage->draw();
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-1.5f, 1.5f, -1.5f, 1.5f, -1.5f, 1.5f);
    //glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angle += (position.x() - _position.x());

        _position = position;

        updateGL();
    }
}

/**
 * @brief GLDisplay::mousePressEvent ajout de la gestion du clic pour ajouter un point dans le maillage (disponique qu'en 3D)
 * @param event
 */
void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    /*if( event != NULL ){
         _position = event->pos();
         if(ajoutPoints){
             float posX = (float)_position.rx()-width()/2;
             float posY = -((float)_position.ry()-height()/2);
             posX = 2*(posX*1.5)/width();
             posY = 2*(posY*1.5)/height();
             int sommet = maillage->creerSommet(Point(posX,posY,0), false,false);
             // gestion des 2 diférents cas soit en incrémental soit en normal
             if (!incremental)
                maillage->ajoutSommet2(sommet);
             else
                 maillage->delonayIncremental(sommet);
             updateGL();
         }

    }*/

}

void GLDisplay::update()
{
    updateGL();
}

