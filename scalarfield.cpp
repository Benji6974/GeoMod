#include "scalarfield.h"

ScalarField::ScalarField()
{

}

int ScalarField::index(int i,int j){
    return i*ny+j;
}
vec3 ScalarField::P(int i,int j){
    vec3 res;
    res.x = a.x+((b.x-a.x)/nx-1)*i ; // voir a quoi correspond ax,bx etc ...
    res.y = a.y+((b.y-a.y)/ny-1)*j ;
    res.z = z[index(i,j)] ;
    return res;
}

double ScalarField::heightGrid(int i,int j){
    // chepa ce que ca fait
    return 0.0;
}

bool ScalarField::inside(int x,int y,int z){
    vec3 zt = P(x,y);
    return z<zt; // test un peu pourri int vs vec3 ??
}

double ScalarField::height(const double& x, const double& y){
    //coordonées locales
    double u=(x-a.x)/(b.x-a.x);
    double v=(y-a.y)/(b.y-a.y);

    //location de la celulle sur la grille
    int nu=int(u*nx);
    int nv=int(v*ny);

    //coordonées locale sur la cellule
    u=u-nu*(b.x-a.x)/nx;
    v=v-nv*(b.y-a.y)/ny;

    if(u+v<1){
        return (1-u-v)*heightGrid(i,j)+u*heightGrid(i+1,j)+v*heightGrid(i,j+1); // completement pourri son code y'a pas de i ni de j !!!
    }else{
        return (u+v-1)*heightGrid(i+1,j+1)+(1-v)*heightGrid(i+1,j)+(1-u)*heightGrid(i,j+1);
    }
}
