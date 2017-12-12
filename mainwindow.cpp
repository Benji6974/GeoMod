#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(10,10);

    ui->openGLWidget->lf = &lf;
    ui->ck_br->setChecked(true);
    connect(ui->pushButtonLoadImage, SIGNAL (released()), this, SLOT (loadImage()));
    connect(ui->pushButtonSaveHFtoObj, SIGNAL (released()), this, SLOT (saveHFtoObj()));
    connect(ui->btn_change_nx_ny, SIGNAL (released()), this, SLOT (changeNxNy()));
    connect(ui->ck_br, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_sable, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_eau, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_montagne, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_total, SIGNAL (released()), this, SLOT (affiche()));



    // nx/ny
    vec2 n = lf.getNxNy();
    ui->box_nx->setRange(0, 1000);
    ui->box_nx->setValue(n.x);
    ui->box_ny->setRange(0, 1000);
    ui->box_ny->setValue(n.y);

    //hauteur
    ui->box_hauteurmin->setRange(0, 1000);
    ui->box_hauteurmin->setValue(0);
    ui->box_hauteurmax->setRange(0, 1000);
    ui->box_hauteurmax->setValue(50);

    // dimentions
    ui->box_dimentionMin->setRange(0, 1000);
    ui->box_dimentionMin->setValue(0);
    ui->box_dimentionMax->setRange(0, 1000);
    ui->box_dimentionMax->setValue(301);

     ui->box_ax->setRange(-1000,1000);
     ui->box_ay->setRange(-1000,1000);
     ui->box_bx->setRange(-1000,1000);
     ui->box_by->setRange(-1000,1000);

     vec2 a = lf.getA();
     vec2 b = lf.getB();
     ui->box_ax->setValue(a.x);
     ui->box_ay->setValue(a.y);
     ui->box_bx->setValue(b.x);
     ui->box_by->setValue(b.y);


}

void MainWindow::affiche(){
    if (ui->ck_br->isChecked())
        ui->openGLWidget->aff = "br";
    if (ui->ck_eau->isChecked())
        ui->openGLWidget->aff = "eau";
    if (ui->ck_montagne->isChecked())
        ui->openGLWidget->aff = "montagne";
    if (ui->ck_sable->isChecked())
        ui->openGLWidget->aff = "sable";
    if (ui->ck_total->isChecked())
        ui->openGLWidget->aff = "total";
    ui->openGLWidget->paintGL();
    ui->openGLWidget->updateGL();
}


void MainWindow::changeNxNy(){
    lf.changeNxNy(vec2(ui->box_nx->value(),ui->box_ny->value()));
}

void MainWindow::changeAB(){
    lf.changeAB(vec2(ui->box_ax->value(),ui->box_ay->value()),vec2(ui->box_bx->value(),ui->box_by->value()));
}

/**
 * @brief MainWindow::LoadImage on affiche une image en niveau de gris representant un scalarField
 */
void MainWindow::loadImage(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open image"), "", tr("images Files (*)"));

    if (ui->ck_br->isChecked() || ui->ck_total->isChecked())
        lf.br.load(fileName,vec2(ui->box_dimentionMin->value(),ui->box_dimentionMin->value()),vec2(ui->box_dimentionMax->value(),ui->box_dimentionMax->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_eau->isChecked() || ui->ck_total->isChecked())
        lf.eau.load(fileName,vec2(ui->box_dimentionMin->value(),ui->box_dimentionMin->value()),vec2(ui->box_dimentionMax->value(),ui->box_dimentionMax->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_montagne->isChecked() || ui->ck_total->isChecked())
        lf.montagne.load(fileName,vec2(ui->box_dimentionMin->value(),ui->box_dimentionMin->value()),vec2(ui->box_dimentionMax->value(),ui->box_dimentionMax->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_sable->isChecked() || ui->ck_total->isChecked())
        lf.sable.load(fileName,vec2(ui->box_dimentionMin->value(),ui->box_dimentionMin->value()),vec2(ui->box_dimentionMax->value(),ui->box_dimentionMax->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());

}

/**
 * @brief MainWindow::saveHFtoObj on sauvegarde une heightmap en obj
 */
void MainWindow::saveHFtoObj(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save obj"), "", tr("Obj files (*.obj)"));

    if (ui->ck_br->isChecked())
        lf.br.save(fileName);
    if (ui->ck_eau->isChecked())
        lf.eau.save(fileName);
    if (ui->ck_montagne->isChecked())
        lf.montagne.save(fileName);
    if (ui->ck_sable->isChecked())
        lf.sable.save(fileName);
    if (ui->ck_total->isChecked())
        //lf.save(fileName); // a decomenter quand save est remontée dans scalarfield
        return;

}

MainWindow::~MainWindow()
{
    delete ui;
}

