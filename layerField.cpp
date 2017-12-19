#include "layerField.h"



LayerField::LayerField(int nx, int ny, vec2 a, vec2 b) : HeightField(nx,ny,a,b){}

LayerField::LayerField(): LayerField(200,200,vec2(),vec2(301.f,301.f))
{

    br = HeightField(200,200,vec2(),vec2(301.f,301.f));
    sable = HeightField(200,200,vec2(),vec2(301.f,301.f));
    eau = HeightField(200,200,vec2(),vec2(301.f,301.f));
    montagne = HeightField(200,200,vec2(),vec2(301.f,301.f));
    vec_HF.push_back(&br);
    vec_HF.push_back(&sable);
    vec_HF.push_back(&eau);
    vec_HF.push_back(&montagne);
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
        this->affiche();
    }else
        return;

}
void LayerField::affiche(){
    HeightField::affiche();
}

void LayerField::heightTotal(){
    for (unsigned int a=0; a<vec_HF.size(); a++){
        std::cout<<"layer "<<a<<std::endl;
        vec2 n = vec_HF[a]->getNxNy();
        this->setNxNy(n);
        for (int x=0; x<n.x; x++ ){
            for (int y=0; y<n.y; y++){

                z[index(x,y)] += vec_HF[a]->heightGrid(x,y);
              // std::cout<<"valeur de z"<< z[index(x,y)] << "j'ajoute"<<vec_HF[a]->heightGrid(x,y)<<std::endl;
            }
        }
    }
}

void LayerField::changeNxNy(vec2 n){
    this->setNxNy(n);
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i]->setNxNy(n);
    }
}

void LayerField::changeAB(vec2 a, vec2 b){
    this->setA(a);
    this->setB(b);
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i]->setA(a);
       vec_HF[i]->setB(b);
    }
}




