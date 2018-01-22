#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->openGLWidget->lf = &lf;
    ui->ck_br->setChecked(true);
    ui->ck_simple->setChecked(true);
    connect(ui->pushButtonLoadImage, SIGNAL (released()), this, SLOT (loadImage()));
    connect(ui->pushButtonSaveHFtoObj, SIGNAL (released()), this, SLOT (saveHFtoObj()));
    connect(ui->btn_change_nx_ny, SIGNAL (released()), this, SLOT (changeNxNy()));
    connect(ui->ck_br, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_sable, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_eau, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_montagne, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->ck_total, SIGNAL (released()), this, SLOT (affiche()));
    connect(ui->btn_calcul_Tot, SIGNAL (released()), this, SLOT (calculTot()));
    connect(ui->btn_saveimg, SIGNAL (released()), this, SLOT (saveHFtojpg()));
    connect(ui->btn_showImg, SIGNAL (released()), this, SLOT (afficheImage()));
    connect(ui->btn_showImageNoise, SIGNAL (released()), this, SLOT (afficheImageNoise()));



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

     nf = NoiseField(n.x,n.y,a,b);

    ui->openGLWidget->aff = "br";
}

void MainWindow::afficheImage(){
    QImage img;
    if (ui->ck_br->isChecked())
        img = lf.br.getImage();
    if (ui->ck_eau->isChecked())
       img = lf.eau.getImage();
    if (ui->ck_montagne->isChecked())
        img = lf.montagne.getImage();
    if (ui->ck_sable->isChecked())
        img = lf.sable.getImage();
    if (ui->ck_total->isChecked()){
        if (ui->ck_simple->isChecked())
            img = lf.getImage();
        if (ui->ck_drainage->isChecked())
            img = lf.drainageField.getImage();
        if (ui->ck_humidite->isChecked())
            img = lf.wetnessField.getImage();
        if (ui->ck_lumiere->isChecked())
            img = lf.luxField.getImage();
        if (ui->ck_slope->isChecked())
            img = lf.slopeField.getImage();
    }

    QPixmap qpix = QPixmap::fromImage(img);
    QSize labelSize = ui->labelImage->size();
    qpix = qpix.scaled(labelSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    ui->labelImage->setPixmap(qpix);
    ui->labelImage->adjustSize();
    ui->labelImage->setScaledContents(true);
}

void MainWindow::afficheImageNoise(){

    std::cout << "generateNoise" << std::endl;
    nf.parameters.setOctaves(ui->spinBoxOctaves->value());
    nf.parameters.setAmplitude(ui->doubleSpinBoxAmplitude->value());
    nf.parameters.setFrequence(ui->doubleSpinBoxFrequence->value());
    nf.parameters.setLacunarity(ui->doubleSpinBoxLacunarite->value());
    nf.parameters.setPersistance(ui->doubleSpinBoxPersistance->value());

    nf.generate(ui->spinBoxSeed->value());

    std::cout << "EndgenerateNoise" << std::endl;

    QImage img;
    img = nf.getImage();

    QPixmap qpix = QPixmap::fromImage(img);
    QSize labelSize = ui->labelImage->size();
    qpix = qpix.scaled(labelSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    ui->labelImage->setPixmap(qpix);
    ui->labelImage->adjustSize();
    ui->labelImage->setScaledContents(true);
}


void MainWindow::calculTot(){
    lf.heightTotal();
    lf.calculSlope();
    lf.ecoulement();
    lf.calculWetness(ui->humiditeFactor->value());
    ui->groupBox_2->setEnabled(true);
    ui->openGLWidget->paintGL();
    ui->openGLWidget->updateGL();
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
        lf.br.load(fileName,vec2(ui->box_ax->value(),ui->box_ay->value()),vec2(ui->box_bx->value(),ui->box_by->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_eau->isChecked() || ui->ck_total->isChecked())
        lf.eau.load(fileName,vec2(ui->box_ax->value(),ui->box_ay->value()),vec2(ui->box_bx->value(),ui->box_by->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_montagne->isChecked() || ui->ck_total->isChecked())
        lf.montagne.load(fileName,vec2(ui->box_ax->value(),ui->box_ay->value()),vec2(ui->box_bx->value(),ui->box_by->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());
    if (ui->ck_sable->isChecked() || ui->ck_total->isChecked())
        lf.sable.load(fileName,vec2(ui->box_ax->value(),ui->box_ay->value()),vec2(ui->box_bx->value(),ui->box_by->value()),ui->box_hauteurmin->value(),ui->box_hauteurmax->value());


}

/**
 * @brief MainWindow::saveHFtoObj on sauvegarde une heightmap en obj
 */
void MainWindow::saveHFtoObj(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save obj"), "", tr("Obj files (*.obj)"));
    bool res = false;
    if (ui->ck_br->isChecked())
        res = lf.br.save(fileName);
    if (ui->ck_eau->isChecked())
        res = lf.eau.save(fileName);
    if (ui->ck_montagne->isChecked())
        res = lf.montagne.save(fileName);
    if (ui->ck_sable->isChecked())
        res = lf.sable.save(fileName);
    if (ui->ck_total->isChecked())
        res = lf.save(fileName);

    if (res)
        QMessageBox::information(this, "OK", "Fichier .obj sauvegardée");
    else
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement");


}

/**
 * @brief MainWindow::saveHFtoObj on sauvegarde une heightmap en obj
 */
void MainWindow::saveHFtojpg(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "",
                                                  tr("Images (*.bmp);;Images (*.jpg);;Images (*.png);;Images (*.ppm);;Images (*.tif);;Images (*.xbm);;Images (*.xpm)"));
    std::cout<<"debut"<<std::endl;
    bool res = false;
    if (ui->ck_br->isChecked())
        res = lf.br.saveImg(fileName);
    if (ui->ck_eau->isChecked())
        res = lf.eau.saveImg(fileName);
    if (ui->ck_montagne->isChecked())
        res = lf.montagne.saveImg(fileName);
    if (ui->ck_sable->isChecked())
        res = lf.sable.saveImg(fileName);
    if (ui->ck_total->isChecked()){
        if (ui->ck_simple->isChecked())
            res = lf.saveImg(fileName);
        if (ui->ck_drainage->isChecked())
            res = lf.drainageField.saveImg(fileName);
        if (ui->ck_humidite->isChecked())
            res = lf.wetnessField.saveImg(fileName);
        if (ui->ck_lumiere->isChecked())
            res = lf.luxField.saveImg(fileName);
        if (ui->ck_slope->isChecked())
            res = lf.slopeField.saveImg(fileName);
    }
    std::cout<<"fin"<<std::endl;


    if (res)
        QMessageBox::information(this, "OK", "Fichier sauvegardée");
    else
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement");


}

MainWindow::~MainWindow()
{
    delete ui;
}

