#ifndef CURVE_H
#define CURVE_H
#pragma once

#include <mathobject.h>
#include <iostream>

#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>

#include <point.h>

using namespace Givaro;
typedef Modular<Integer> Field;

class Curve: public MathObject
{
public:

    Field::Element a1, a2, a3, a4, a6;
    Integer discriminant;
    bool IsWeierstrassForm;

    Curve(Integer field, Integer a1, Integer a2, Integer a3,  Integer a4, Integer a6);
    Curve(Integer field, Integer a, Integer b);
    Curve(Integer field, int a, int b);
    Curve(Integer field);

    Curve(Field field, Integer a1, Integer a2, Integer a3,  Integer a4, Integer a6);
    Curve(Field field, Integer a, Integer b);
    Curve(Field field, int a, int b);
    Curve(Field field);

    bool IsSingular();    
    Integer ComputeDiscriminant();
    bool IsPointOnCurve(Point p); 

    Point PointAddition(Point p, Point q);
    Point PointDoubling(Point p);
    Point PointSummary(Point p, Point q);

    Integer ComputeYFromX(Field::Element &result, Integer x);
        
    
    friend std::ostream & operator<< (std::ostream & out, const Curve& ptr);


};

#endif // CURVE_H
