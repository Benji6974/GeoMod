#include "layerField.h"

Veget::Veget()
{
    arbres.push_back(tree("sapin",
                        vec2(40,80), // hauteur
                         vec2(20,80), //humidite
                         vec2(40,100), //lumiere
                         vec2(0,40), //pente
                         vec2(0,20), //streampower
                         10
                         ));
    arbres.push_back(tree("pommier",
                        vec2(0,60), // hauteur
                         vec2(30,80), //humidite
                         vec2(50,100), //lumiere
                         vec2(0,20), //pente
                         vec2(0,20), //streampower
                         15
                         ));


}

double Veget::fcntTransfert(vec2 val, double test){
    double difference = val.y -val.x;
    double centre = val.x+(difference/2);
    return 1 - (test-val.x/difference);
}


void Veget::poisson(LayerField lf){

    Vec2f x_min;
    x_min[0] = lf.getA().x;
    x_min[1] = lf.getA().y;
    Vec2f x_max;
    x_max[0] = lf.getB().x;
    x_max[1] = lf.getB().y;
    /*uint32_t max_sample_attempts = 50;
    uint32_t seed = 9429;*/
    std::vector<Vec2f> samples = thinks::poissonDiskSampling(arbres[0].radius, x_min, x_max);
    std::vector<vec3> arbresPlantee;
     for (unsigned int i = 0; i < samples.size(); ++i) {
         lf.height(vec2(samples[i][0],samples[i][0]));
         double rnd = ((double) rand() / (RAND_MAX));
         std::vector<double> res;
         res.push_back(fcntTransfert(arbres[0].hauteur, lf.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(arbres[0].humidite, lf.wetnessField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(arbres[0].lumiere, lf.luxField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(arbres[0].pente, lf.slopeField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(arbres[0].streampower, lf.streamPower.height(vec2(samples[i][0],samples[i][1]))));

         double densiteVeget = res[i];
        for(int y=1; y< res.size(); y++){
            densiteVeget = std::min(densiteVeget,res[i]);
        }
         if (rnd < densiteVeget){
             arbresPlantee.push_back(vec3(samples[i][0],samples[i][1],lf.height(vec2(samples[i][0],samples[i][1]))));
         }

     }




}
