#include "layerField.h"

LayerField::LayerField()
{
    br = HeightField(100,100,vec2(),vec2(1.f,1.f));
    br.load(QString("/circuit.png"),vec2(),vec2(500,500),1,500);
    br.save(QString("/circuit.obj"));
}

void LayerField::affiche(){
    br.affiche();
}


