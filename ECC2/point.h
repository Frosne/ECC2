#pragma once

#ifndef POINT_H
#define POINT_H

#include <mathobject.h>
#include <iostream>

#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>

using namespace Givaro;
typedef Modular<Integer> Field;

class Point: public MathObject
{
public:
    Point(Integer field);
    Point(Integer field, Integer x, Integer y);
    Point(Field fld, Integer x, Integer y);
    bool IsEqual(const Point& p1) const;
    Field::Element x, y;
    friend std::ostream & operator<< (std::ostream & out, const Point& ptr);

};

#endif // POINT_H
