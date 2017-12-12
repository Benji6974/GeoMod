#include "layerField.h"



LayerField::LayerField(int nx, int ny, vec2 a, vec2 b) : ScalarField(nx,ny,a,b){}

LayerField::LayerField(): LayerField(200,200,vec2(),vec2(1.f,1.f))
{
    vec_HF.push_back(br);
    vec_HF.push_back(sable);
    vec_HF.push_back(eau);
    vec_HF.push_back(montagne);
    br = HeightField(200,200,vec2(),vec2(1.f,1.f));
    sable = HeightField(200,200,vec2(),vec2(1.f,1.f));
    eau = HeightField(200,200,vec2(),vec2(1.f,1.f));
    montagne = HeightField(200,200,vec2(),vec2(1.f,1.f));
}

void LayerField::affiche(std::string str){
    if (str == "br")
        br.affiche();
    else if(str == "sable")
        sable.affiche();
    else if(str == "eau")
        eau.affiche();
    else if(str == "montagne")
        montagne.affiche();
    else if(str == "total"){
        heightTotal();
        this->affiche();
    }else
        return;

}
void LayerField::affiche(){
    ScalarField::affiche();
}

void LayerField::heightTotal(){
    for (unsigned int a=0; a<vec_HF.size(); a++){

        for (int x=0; x<nx-1; x++ ){
            for (int y=0; y<ny-1; y++){
                z[index(x,y)] += vec_HF[a].height(vec2(x,y));
            }
        }
    }
}

void LayerField::changeNxNy(vec2 n){
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i].setNxNy(n);
    }
}

void LayerField::changeAB(vec2 a, vec2 b){
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i].setA(a);
       vec_HF[i].setB(b);
    }
}


