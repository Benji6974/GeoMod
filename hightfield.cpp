#include "hightfield.h"

HightField::HightField()
{

}

void HightField::load(std::string img,vec2 a, vec2 b,float za, float zb){
    Image image= read_image(img.c_str());
       if(image == Image::error())
           std::cout<<"erreur de chargement"<<std::endl;

       //int gris[image.width()][image.height()];
       float gris;
       float scaling = 8;
       int x,y;

       for (y=0;y<image.width()-1;y++)
       {
           std::vector<ScalarField> val;
           for (x=0;x<image.height()-1;x++)
           {
               ScalarField t;
               Color col = image(x, y);
               Color col2 = image(x+1, y);
               Color col3 = image(x, y+1);
               Color col4 = image(x+1, y+1);

               float x1 = x/scaling;
               float x2 = (x+1)/scaling;
               float x3 = x/scaling;
               float x4 = (x+1)/scaling;
               float y1 = y/scaling;
               float y2 = y/scaling;
               float y3 = (y+1)/scaling;
               float y4 = (y+1)/scaling;
               float z1 = (float)(((col.r+col.g+col.b)/3*255-130))/scaling;
               float z2 = (float)(((col2.r+col2.g+col2.b)/3*255-130))/scaling;
               float z3 = (float)(((col3.r+col3.g+col3.b)/3*255-130))/scaling;
               float z4 = (float)(((col4.r+col4.g+col4.b)/3*255-130))/scaling;

                // ca calculais les normales et triangles
               /*unsigned int a = mesh_.vertex(x1, y1, z1 );
               unsigned int b = mesh_.vertex(x2, y2, z2 );
               unsigned int c = mesh_.vertex(x3, y3, z3 );
               unsigned int d = mesh_.vertex(x4, y4, z4 );
               //std::cout<<(float)(col.r+col.g+col.b)/3*255<<std::endl;
               mesh_.normal((y2-y1)*(z3-z1)-(z2-z1)*(y3-y1),(z2-z1)*(x3-x1) - (x2-x1)*(z3-z1),(x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
               mesh_.triangle(a, b, c);
               mesh_.normal((y3-y4)*(z2-z4)-(z3-z4)*(y2-y4),(z3-z1)*(x2-x4) - (x3-x4)*(z2-z4),(x3-x4)*(y2-y4) - (y3-y4)*(x2-x4));
               mesh_.triangle(d, c, b);
               t.setHauteur((float)(((col.r+col.g+col.b)/3*255-130))/scaling);
               t.setNormal(normalize(Vector(((y2-y1)*(z3-z1)-(z2-z1)*(y3-y1),(z2-z1)*(x3-x1) - (x2-x1)*(z3-z1),(x2-x1)*(y3-y1) - (y2-y1)*(x3-x1))*Vector((y3-y4)*(z2-z4)-(z3-z4)*(y2-y4),(z3-z1)*(x2-x4) - (x3-x4)*(z2-z4),(x3-x4)*(y2-y4) - (y3-y4)*(x2-x4))/2)));

               //MARCHEBOF t.setNormal(Vector((y2-y1)*(z3-z1)-(z2-z1)*(y3-y1),(z2-z1)*(x3-x1) - (x2-x1)*(z3-z1),(x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)+1));*/
               //val.push_back(t);
           }
           //tab.push_back(val);

       }
}
