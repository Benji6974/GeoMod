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
    streamPower = ScalarField(200,200,vec2(),vec2(301.f,301.f));

    vec_HF.push_back(&br);
    vec_HF.push_back(&sable);
    vec_HF.push_back(&eau);
    vec_HF.push_back(&montagne);

    vegetation = Veget();
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
    vegetation.afficheArbres();
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
    this->setAllZ(0);
    for (unsigned int i=0; i<vec_HF.size(); i++){
       vec_HF[i]->setNxNy(n);
       vec_HF[i]->changeSizeZ();
       vec_HF[i]->setAllZ(0);
    }
    slopeField.setNxNy(n);
    wetnessField.setNxNy(n);
    luxField.setNxNy(n);
    drainageField.setNxNy(n);
    streamPower.setNxNy(n);

    slopeField.changeSizeZ();
    wetnessField.changeSizeZ();
    luxField.changeSizeZ();
    drainageField.changeSizeZ();
    streamPower.changeSizeZ();


    slopeField.setAllZ(0);
    wetnessField.setAllZ(0);
    luxField.setAllZ(0);
    drainageField.setAllZ(0);
    streamPower.setAllZ(0);


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
    streamPower.setA(a);

    slopeField.setB(b);
    wetnessField.setB(b);
    luxField.setB(b);
    drainageField.setB(b);
    streamPower.setB(b);

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
    std::vector<vec2i> v;
    getVoisin((int) pos.x, (int) pos.y, v);

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

void LayerField::calculPowerStream(){
    streamPower.setAllZ(0);
    for(int x = 1 ; x < this->nx-1 ; x++){
        for(int y = 1 ; y < this->ny-1 ; y++){
           streamPower.setZ(x,y, std::sqrt(drainageField.getZ(x, y))*slopeField.getZ(x, y));
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


void LayerField::calculErosion() //on considère l'érosion sur 10 ans (pour être le plus réaliste possible)
{
    double removeBrMax = 0.5; //0.5 mètre si lum = 100%
    for(int x = 0 ; x < this->nx ; x++){
        for(int y = 0 ; y < this->ny ; y++){
            double removeValue = std::max(0.0, removeBrMax*luxField.getZ(x,y) - sable.getZ(x,y));
            removeValue = std::min(br.getZ(x,y), removeValue);
            br.setZ(x,y, br.getZ(x,y) -  removeValue);
            sable.setZ(x,y, sable.getZ(x,y) + removeValue);
        }
    }
    stabilization();
}

double LayerField::getTanAngle(int x1, int y1, int x2, int y2)
{
    //on considère en z que x1,y1 > x2,y2
    double diffH = abs(getZ(x1, y1) - getZ(x2, y2));
    //double diffXY = abs(Vertex(x1, y1) - Vertex(x2, y2));
    double diffXY = 1;
    return diffH / diffXY;
}

void LayerField::stabilization()
{
    std::vector<int> randValueX;
    randValueX.resize(nx);
    std::vector<int> randValueY;
    randValueY.resize(ny);

    std::iota(randValueX.begin(), randValueX.end(), 0);
    std::default_random_engine engine(4856);
    std::shuffle(randValueX.begin(), randValueX.end(), engine);
    std::iota(randValueY.begin(), randValueY.end(), 0);
    std::default_random_engine engine2(1247);
    std::shuffle(randValueY.begin(), randValueY.end(), engine2);

    std::deque<vec2i> haveToUpdate;

    for(int x = 0 ; x < this->nx ; x++){
        for(int y = 0 ; y < this->ny ; y++){
            ecoulementVoisin(haveToUpdate, randValueX[x], randValueY[y], 40);
        }
    }

    //on verifie l'écoulement sur les voisins mis a jour précédament
    //on continue jusqu'a que tout soit stable = plus de point a vérifier
    while(!haveToUpdate.empty())
    {
        vec2i pos = haveToUpdate.front();
        ecoulementVoisin(haveToUpdate, pos.x, pos.y, 40);
        haveToUpdate.pop_front();
    }

}

void LayerField::ecoulementVoisin(std::deque<vec2i> & haveToUpdate, int x , int y, double angleMax)
{
    std::vector<vec2i> voisins;
    getVoisin(x,y, voisins);
    std::default_random_engine engine3(x + y);
    std::shuffle(voisins.begin(), voisins.end(), engine3);

    //on parcours les voisins au hasard
    for(unsigned int i = 0 ; i < voisins.size() ; i++)
    {
        //si il reste pas de sable a ecouler on stoppe
        if(sable.getZ(x,y) == 0)
            break;

        //si le voisin est plus bas
        if(getZ(x,y) > getZ(voisins[i].x,voisins[i].y))
        {

            double result = getTanAngle(x, y,voisins[i].x, voisins[i].y) - tan(angleMax * M_PI / 180.0 );
            if(result > 0) //eboulement
            {
                    //on calcule la quantite a deverser pour que l'angle obtenu ne dépasse plus angleMax
                    double diffHOK = std::min(result / 2.0, sable.getZ(x,y));

                    sable.setZ(x,y, sable.getZ(x,y) - diffHOK);
                    sable.setZ(voisins[i].x,voisins[i].y, sable.getZ(voisins[i].x,voisins[i].y) + diffHOK);

                    setZ(x,y, getZ(x,y) - diffHOK);
                    setZ(voisins[i].x,voisins[i].y, getZ(voisins[i].x,voisins[i].y) + diffHOK);

                    if(std::find(haveToUpdate.begin(), haveToUpdate.end(), vec2i(voisins[i].x, voisins[i].y)) == haveToUpdate.end())
                        haveToUpdate.push_back(vec2i(voisins[i].x, voisins[i].y));
            }
        }
    }

}


void LayerField::calculLumiere(int nbSrcLum, int nbPas){
    luxField.setAllZ(0);

    // Génération de nos sources de lumières
    //vec2 centre = getCenter();
    //VAR_TYPE radius = distance(centre, a) + distance(centre, a)/10;
    vec3 center = vec3(b.x/2,b.y/2, 0.0);
    float radius = (b.x/2)*1.01;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    std::vector<vec3> listPoints(nbSrcLum);

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
    std::cout<<"rayon "<<radius<<std::endl;

    // Lancer de rayons
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            vec3 depart(P(i,j));
            //std::cout<< "coucou"<<endl;
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


void LayerField::calculPoisson(){
    vegetation.poisson(*this);
}

QImage LayerField::getImageArbres(){
    return vegetation.getImageArbres(*this);
}

