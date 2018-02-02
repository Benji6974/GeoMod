#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include "layerField.h"
#include "noiseField.h"
#include <QCoreApplication>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QCheckBox>
#include <QMessageBox>
#include <ctime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    LayerField lf;
    NoiseField nf;
    std::clock_t start;
    double duration;

private slots:
    void loadImage();
    void saveHFtoObj();
    void changeNxNy();
    void affiche();
    void changeAB();
    void calculTot();
    void saveHFtojpg();
    void afficheImage();
    void afficheImageNoise();
    void saveNFtoImg();
    void upScale();
    void downScale();
    void calculErosion();
};

#endif // MAINWINDOW_H
