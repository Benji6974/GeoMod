#include "scalarField.h"

ScalarField::ScalarField()
{
    z = QVector<double>();
}

ScalarField::ScalarField(int nx, int ny, vec2 a, vec2 b): Array2(nx,ny,a,b)
{
    z = QVector<double>(nx*ny);
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
    return P(i,j).z;
}

bool ScalarField::inside(int x,int y,int z){
    vec3 zt = P(x,y);
    return z<zt.z; // test un peu pourri int vs vec3 ??
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
        return (1-u-v)*heightGrid(nu,nv)+u*heightGrid(nu+1,nv)+v*heightGrid(nu,nv+1); // completement pourri son code y'a pas de i ni de j !!!
    }else{
        return (u+v-1)*heightGrid(nu+1,nv+1)+(1-v)*heightGrid(nu+1,nv)+(1-u)*heightGrid(nu,nv+1);
    }
}



void ScalarField::load(QString pathFile, vec2 a, vec2  b, float za, float zb){

    this->a = a;
    this->b = b;

    //QString pathFile = QDir::currentPath() + relativePathFileName;
    QImage img(pathFile);

    if(img.isNull())
        return;

    img.scaled(nx,ny);

    for(int i = 0 ; i < this->nx ; i++)
    {
        for(int j = 0 ; j < this->ny ; j++)
        {
            int value =  qGray(img.pixel(i,j));
            double h = ((double)value/255.f)*(zb-za) + za;
            z[index(i,j)] = h;
        }
    }

    std::cout<<"Image lue"<<std::endl;

}
