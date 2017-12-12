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

    // nx/ny
    ui->box_nx->setRange(0, 1000);
    ui->box_nx->setValue(200);
    ui->box_ny->setRange(0, 1000);
    ui->box_ny->setValue(200);

    //hauteur
    ui->box_hauteurmin->setRange(0, 1000);
    ui->box_hauteurmin->setValue(0);
    ui->box_hauteurmax->setRange(0, 1000);
    ui->box_hauteurmax->setValue(50);

    //
    ui->box_dimentionMin->setRange(0, 1000);
    ui->box_dimentionMin->setValue(0);
    ui->box_dimentionMax->setRange(0, 1000);
    ui->box_dimentionMax->setValue(301);
}

/**
 * @brief MainWindow::LoadImage on affiche une image en niveau de gris representant un scalarField
 */
void MainWindow::loadImage(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open image"), "", tr("images Files (*)"));
    lf.br.load(fileName,vec2(ui->box_dimentionMin->value(),ui->box_dimentionMin->value()),vec2(ui->box_dimentionMax->value(),ui->box_dimentionMax->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
}

/**
 * @brief MainWindow::saveHFtoObj on sauvegarde une heightmap en obj
 */
void MainWindow::saveHFtoObj(){

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save obj"), "", tr("Obj files (*.obj)"));
    lf.br.save(fileName);

}

MainWindow::~MainWindow()
{
    delete ui;
}

