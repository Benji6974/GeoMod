#include "layerField.h"

LayerField::LayerField()
{
    br = HeightField(200,200,vec2(),vec2(1.f,1.f));
    //br.load(QString("/terrain_redimensionner.jpg"),vec2(),vec2(301,301),1,40);
    //br.save(QString("/terrain_redimensionner.obj"));
}

void LayerField::affiche(){
    br.affiche();
}


