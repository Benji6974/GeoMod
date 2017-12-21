#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include "layerField.h"
#include <QCoreApplication>
#include <QGraphicsTextItem>
#include <QFont>
 #include <QFileDialog>
 #include <QTextStream>
 #include <QFile>
#include <QCheckBox>
#include <QMessageBox>

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

private slots:
    void loadImage();
    void saveHFtoObj();
    void changeNxNy();
    void affiche();
    void changeAB();
    void calculTot();
    void tri();
    void saveHFtojpg();
};

#endif // MAINWINDOW_H
