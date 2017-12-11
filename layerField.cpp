#include "layerField.h"

LayerField::LayerField()
{
    br = HeightField(10,10,vec2(),vec2(1.f,1.f));
}

void LayerField::affiche(){
    br.affiche();
}


