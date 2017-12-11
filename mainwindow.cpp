#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QGraphicsTextItem>
#include <QFont>
 #include <QFileDialog>
 #include <QTextStream>
 #include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(10,10);

    ui->openGLWidget->lf = &lf;
    connect(ui->pushButtonLoadImage, SIGNAL (released()), this, SLOT (loadImage()));
    connect(ui->pushButtonSaveHFtoObj, SIGNAL (released()), this, SLOT (saveHFtoObj()));

    lf = LayerField();
}

/**
 * @brief MainWindow::LoadImage on affiche une image en niveau de gris representant un scalarField
 */
void MainWindow::loadImage(){


}

/**
 * @brief MainWindow::saveHFtoObj on sauvegarde une heightmap en obj
 */
void MainWindow::saveHFtoObj(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

