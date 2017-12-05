#include <QCoreApplication>
#include "heightField.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HeightField hf2 = HeightField(1000,1000,vec2(),vec2(1.f,1.f));
    hf2.load(QString("/circuit.png"),vec2(),vec2(500,500),1,500);
    hf2.save(QString("/circuit.obj"));
    return a.exec();
}


