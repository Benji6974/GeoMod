#include <QCoreApplication>
#include "scalarField.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ScalarField sf2 = ScalarField(1024,1024,vec2(),vec2(1.f,1.f));
    sf2.load(QString("circuit.png"),vec2(),vec2(500,500),10,1000);

    return a.exec();
}


