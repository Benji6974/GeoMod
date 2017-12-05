#include <QCoreApplication>
#include "heightField.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HeightField hf2 = HeightField(1024,1024,vec2(),vec2(1.f,1.f));
    hf2.load(QString("C:/Users/Benji/workspace/M2/GeoMod/circuit.png"),vec2(),vec2(500,500),10,1000);
    hf2.save();
    return a.exec();
}


