#include <QApplication>
#include "heightField.h"
#include "mainwindow.h"
#include <noiseField.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    //HeightField hf2 = HeightField(400,400,vec2(),vec2(1.f,1.f));
    //hf2.load(QString("/circuit.png"),vec2(),vec2(500,500),1,500);
    //hf2.save(QString("/circuit.obj"));

    //NoiseField noiseTest = NoiseField(200,200,vec2(),vec2(1.f,1.f));
    //noiseTest.generate();
    //noiseTest.saveImg("testNoiseStruct.png");

    return a.exec();
}
