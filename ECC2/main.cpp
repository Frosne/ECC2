#include <iostream>
#include <math.h>
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>
#include <point.h>
#include <algorithms.h>
#include <curve.h>
#include <list>

using namespace Givaro;
typedef Modular<Integer> Field;

int main() {

    Field fld (17);
    Field::Element test;
    Curve c (17,-5,7);
    std::list<Point> lst = Algorithms::ComputeAllPointsOnCurve(fld, c);
    std::list<Point>::iterator it;

    for (it = lst.begin(); it!=lst.end(); it++)
        std::cout<<*it<<std::endl;
}
