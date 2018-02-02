#include "layerField.h"

Veget::Veget()
{
    arbres.push_back(tree("sapin",
                        vec2(40,80), // hauteur
                         vec2(20,80), //humidite
                         vec2(40,100), //lumiere
                         vec2(0,40), //pente
                         vec2(0,20), //streampower
                         4
                         ));
    arbres.push_back(tree("pommier",
                        vec2(0,60), // hauteur
                         vec2(30,80), //humidite
                         vec2(50,100), //lumiere
                         vec2(0,20), //pente
                         vec2(0,20), //streampower
                         5
                         ));


}

double Veget::fcntTransfert(vec2 val, double test){
    double difference = val.y -val.x;
    double centre = val.x+(difference/2);
    return 1 - (test-centre/difference);
}


void Veget::poisson(LayerField &lf){

    Vec2f x_min;
    x_min[0] = lf.getA().x;
    x_min[1] = lf.getA().y;
    Vec2f x_max;
    x_max[0] = lf.getB().x;
    x_max[1] = lf.getB().y;
    std::vector<Vec2f> samples = thinks::poissonDiskSampling(arbres[0].radius, x_min, x_max);
    arbresPlantee.clear();

    vec2 totMinMax = lf.calculMinMax();
    vec2 humMinMax = lf.wetnessField.calculMinMax();
    vec2 luxMinMax = lf.luxField.calculMinMax();
    vec2 slopeMinMax = lf.slopeField.calculMinMax();
    vec2 streampowerMinMax = lf.streamPower.calculMinMax();

    vec2 tmp_h = vec2((arbres[0].hauteur.x*totMinMax.x)/100,(arbres[0].hauteur.y*totMinMax.y)/100 );
    vec2 tmp_hum =  vec2((arbres[0].humidite.x*humMinMax.x)/100,(arbres[0].humidite.y*humMinMax.y)/100 );
    vec2 tmp_lux = vec2((arbres[0].lumiere.x*luxMinMax.x)/100,(arbres[0].lumiere.y*luxMinMax.y)/100 );
    vec2 tmp_pente = vec2((arbres[0].pente.x*slopeMinMax.x)/100,(arbres[0].pente.y*slopeMinMax.y)/100 );
    vec2 tmp_streampower = vec2((arbres[0].streampower.x*streampowerMinMax.x)/100,(arbres[0].streampower.y*streampowerMinMax.y)/100 );

     for (unsigned int i = 0; i < samples.size(); ++i) {
         lf.height(vec2(samples[i][0],samples[i][0]));
         double rnd = ((double) rand() / (RAND_MAX));
         std::vector<double> res;

         res.push_back(fcntTransfert(tmp_h, lf.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(tmp_hum, lf.wetnessField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(tmp_lux, lf.luxField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(tmp_pente, lf.slopeField.height(vec2(samples[i][0],samples[i][1]))));
         res.push_back(fcntTransfert(tmp_streampower, lf.streamPower.height(vec2(samples[i][0],samples[i][1]))));

         double densiteVeget = res[i];
        for(unsigned int y=1; y< res.size(); y++){
            densiteVeget = std::min(densiteVeget,res[i]);
        }

         if (rnd < densiteVeget){
             arbresPlantee.push_back(vec3(samples[i][0],samples[i][1],lf.height(vec2(samples[i][0],samples[i][1]))));
         }
     }
}


void Veget::afficheArbres(){
    for (unsigned int r =0;r< arbresPlantee.size();r++){
        glLineWidth(1);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
        float scale = 0.05;
        glVertex3f(arbresPlantee[r].x*scale, arbresPlantee[r].y*scale, arbresPlantee[r].z*scale);
        glVertex3f(arbresPlantee[r].x*scale, arbresPlantee[r].y*scale, (arbresPlantee[r].z+10)*scale);

        glEnd();
    }
}

QImage Veget::getImageArbres(LayerField &lf){

    float nx = lf.getNxNy().x;
    float ny = lf.getNxNy().y;
    vec2 b= lf.getB();



    QImage img = QImage(nx,ny,QImage::Format_RGB32);
    std::cout<<"debut gen image"<<std::endl;
    if(nx + ny < 1)
        return img;

    for (unsigned int r =0;r< arbresPlantee.size();r++){
        int x = (arbresPlantee[r].x/b.x)*nx;
        int y = (arbresPlantee[r].y/b.y)*ny;
        QColor s;
        s.setHsv(123,100,72);
        img.setPixelColor(x,y,s);
    }

    std::cout<<"fin gen image"<<std::endl;
    QTransform t;
    return img.transformed(t.rotate(90));



}

