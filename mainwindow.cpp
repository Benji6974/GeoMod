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
    ui->graphicsView->scale(100,100);

    connect(ui->loadOff, SIGNAL (released()), this, SLOT (ouvrirFichier()));
    connect(ui->saveOff, SIGNAL (released()), this, SLOT (saveFichier()));

}

/**
 * @brief MainWindow::ouvrirFichier on load le fichier selectionnée
 */
void MainWindow::ouvrirFichier(){

}

/**
 * @brief MainWindow::saveFichier on sauvegarde le fichier selectionnée à la facon OFF (Sommet + faces mais pas les arretes
 */
void MainWindow::saveFichier(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

