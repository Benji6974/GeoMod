#include "heightField.h"



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

HeightField::HeightField()
{

}

HeightField::HeightField(int nx, int ny, vec2 a, vec2 b) : ScalarField(nx,ny,a,b){}
