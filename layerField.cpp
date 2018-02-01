#include "layerField.h"



LayerField::LayerField(int nx, int ny, vec2 a, vec2 b) : HeightField(nx,ny,a,b){}

LayerField::LayerField(): LayerField(200,200,vec2(),vec2(301.f,301.f))
{

    br = HeightField(200,200,vec2(),vec2(301.f,301.f));
    sable = HeightField(200,200,vec2(),vec2(301.f,301.f));
    eau = HeightField(200,200,vec2(),vec2(301.f,301.f));
    montagne = HeightField(200,200,vec2(),vec2(301.f,301.f));

    slopeField = ScalarField(200,200,vec2(),vec2(301.f,301.f));
    wetnessField = ScalarField(200,200,vec2(),vec2(301.f,301.f));
    luxField = ScalarField(200,200,vec2(),vec2(301.f,301.f));
    drainageField = ScalarField(200,200,vec2(),vec2(301.f,301.f));
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
    this->setAllZ(0);
    for (unsigned int a=0; a<vec_HF.size(); a++){
        std::cout<<"layer "<<a<<std::endl;
        vec2 n = vec_HF[a]->getNxNy();
        this->setNxNy(n);
        for (int x=0; x<n.x; x++ ){
            for (int y=0; y<n.y; y++){

                z[index(x,y)] += vec_HF[a]->heightGrid(x,y);
               //std::cout<<"valeur de z"<< z[index(x,y)] << "j'ajoute"<<vec_HF[a]->heightGrid(x,y)<<std::endl;
            }
        }
    }
}

void LayerField::changeNxNy(vec2 n){
    this->setNxNy(n);
        changeSizeZ();
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i]->setNxNy(n);
       vec_HF[i]->changeSizeZ();
    }
    slopeField.setNxNy(n);
    wetnessField.setNxNy(n);
    luxField.setNxNy(n);
    drainageField.setNxNy(n);


    slopeField.changeSizeZ();
    wetnessField.changeSizeZ();
    luxField.changeSizeZ();
    drainageField.changeSizeZ();
}

void LayerField::changeAB(vec2 a, vec2 b){
    this->setA(a);
    this->setB(b);

    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i]->setA(a);
       vec_HF[i]->setB(b);

    }
    slopeField.setA(a);
    wetnessField.setA(a);
    luxField.setA(a);
    drainageField.setA(a);

    slopeField.setB(b);
    wetnessField.setB(b);
    luxField.setB(b);
    drainageField.setB(b);

}

std::vector<vec3> LayerField::tri(){
    return HeightField::tri();
}

void LayerField::ecoulement(){
    drainageField.setAllZ(1);
    std::cout<< "slope OK"<<std::endl;
    std::vector<vec3> sftri = tri();
    for(unsigned int a = 0 ; a < sftri.size() ; a++){
        majVoisinEcoulement(sftri[a]);
    }
}

void LayerField::majVoisinEcoulement(vec3 pos){
    std::vector<vec2> v = std::vector<vec2>();
    if (pos.x+1 < nx){
        v.push_back(vec2(pos.x+1,pos.y));
        if (pos.y+1 < ny)
            v.push_back(vec2(pos.x+1,pos.y+1));
        if (pos.y-1 > 0)
            v.push_back(vec2(pos.x+1,pos.y-1));
    }
    if (pos.x-1 > 0){
        v.push_back(vec2(pos.x-1,pos.y));
        if (pos.y+1 < ny)
            v.push_back(vec2(pos.x-1,pos.y+1));
        if (pos.y-1 > 0)
            v.push_back(vec2(pos.x-1,pos.y-1));
    }
    if (pos.y+1 < ny)
        v.push_back(vec2(pos.x,pos.y+1));
    if (pos.y-1 > 0)
        v.push_back(vec2(pos.x,pos.y-1));

    double somme=0;
    for(unsigned int i = 0; i<v.size(); i++){
        if (getZ(v[i].x,v[i].y) < getZ(pos.x,pos.y) )
            somme += slopeField.getZ(v[i].x,v[i].y);
    }
    if (somme != 0.0){
        double val = drainageField.getZ(pos.x,pos.y);
        for(unsigned int i = 0; i<v.size(); i++){
            if (getZ(v[i].x,v[i].y) < getZ(pos.x,pos.y)){
                double pourcentage = (slopeField.getZ(v[i].x,v[i].y))/(somme);
                drainageField.setZ(v[i].x,v[i].y,drainageField.getZ(v[i].x,v[i].y)+(val*pourcentage));

            }
        }

    }

}

double LayerField::slope(int i, int j){
    vec2 gr = Gradiant(i,j);
    return sqrt(gr.x*gr.x + gr.y*gr.y);
}

void LayerField::calculSlope(){
    slopeField.setAllZ(1);
    for(int x = 1 ; x < this->nx-1 ; x++){
        for(int y = 1 ; y < this->ny-1 ; y++){
           slopeField.setZ(x,y, slope(x, y));
        }
    }
}


//weatness index W = ln(A/1+ks) k un param 1 2 ou plus en fonction de la pente pour l'accentuer ou non


void LayerField::calculWetness(float param){
    wetnessField.setAllZ(0);
    for(int x = 1 ; x < this->nx-1 ; x++){
        for(int y = 1 ; y < this->ny-1 ; y++){
                wetnessField.setZ(x,y, log(drainageField.getZ(x,y)/(param+slopeField.getZ(x,y))));
        }
    }
}

void LayerField::calculLumiere(int nbSrcLum, int nbPas){
    luxField.setAllZ(0);

    // Génération de nos sources de lumières
    //vec2 centre = getCenter();
    //VAR_TYPE radius = distance(centre, a) + distance(centre, a)/10;
    vec3 center = vec3(b.x/2,b.y/2, 0.0);
    float radius = (a.x/2)*1.01;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    std::vector<vec3> listPoints(nbSrcLum);
    std::cout<< "coucou"<<endl;
    for(int i = 0; i < nbSrcLum; ++i) {
        double theta = 2 * M_PI * uniform(generator);
        double phi = acos(1 - 2 * uniform(generator));

        double x = center.x + radius * sin(phi) * cos(theta);
        double y = center.y + radius * sin(phi) * sin(theta);
        double z = center.z + radius * cos(phi);

        vec3 point(x, y, z);

        // Si point dans l'hemisphere inférieur, on inverse z
        if(point.z < 0) {
            point.z = -point.z;
        }

        listPoints[i] = point;
    }


    // Lancer de rayons
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            vec3 depart(P(i,j));

            for(unsigned int p = 0; p < listPoints.size(); ++p) {
                vec3 rayon = listPoints[p] - depart;
                bool visible = true;

                // On ne parcourt que la 1ère moitié du rayon
                for(float k = 1; k <= nbPas/2; ++k) {
                    vec3 rayPos = depart + (rayon * (k/nbPas));
                    if(underTerrain(rayPos)) {
                        visible = false;
                        break;
                    }
                }

                if(visible){
                    luxField.setZ(i, j,luxField.getZ(i,j)+1);
                }
            }
        }
    }

}



