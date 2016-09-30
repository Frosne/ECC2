#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>

#include <list>
#include <curve.h>

using namespace Givaro;
typedef Modular<Integer> Field;
typedef std::list<Point> Points;

class  Algorithms
{
public:
    Algorithms();
    static Points ComputeAllPointsOnCurve(Field fld, Curve c);
    static Integer power (Integer number, int power);
    static Integer power (Field fld, Integer number, int power);
    static Integer SquareRoot(Field::Element & result, Field fld, Integer element);

};

#endif // ALGORITHMS_H
