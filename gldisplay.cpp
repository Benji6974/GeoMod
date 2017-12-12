#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angleX(0.0f),
    _angleY(0.0f),
    _deplacementX(0.0f),
    _deplacementY(0.0f),
    aff("")
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


    glTranslatef(_deplacementX,_deplacementY,0.f);
    glRotatef(_angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(_angleY, 1.0f, 0.0f, 0.0f);

    lf->affiche(aff);
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-10.5f, 10.5f, -10.5f, 10.5f, -10.5f, 10.5f);
    //glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{

    if( event != NULL ) {
        std::cout<<event->buttons()<<std::endl;
        if (event->buttons() == Qt::RightButton){
            QPoint position = event->pos();
            _angleX += (position.x() - _position.x());
            _angleY += (position.y() - _position.y());
            _position = position;
             updateGL();
        }else{
            QPoint position = event->pos();
            _deplacementX += (position.x() - _position.x())*0.08;
            _deplacementY -= (position.y() - _position.y())*0.08;
            _position = position;

            updateGL();
        }

    }
}

/**
 * @brief GLDisplay::mousePressEvent ajout de la gestion du clic pour ajouter un point dans le maillage (disponique qu'en 3D)
 * @param event
 */
void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL ){
         _position = event->pos();
        /* if(ajoutPoints){
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
         }*/

    }

}

void GLDisplay::update()
{
    updateGL();
}

