#include "point.h"
#include <iostream>


Point::Point(Integer field)
{
    Modular<Integer> _field (field);
    this->field = _field;
}

Point::Point(Integer field, Integer x, Integer y)
{
    Modular<Integer> _field(field);
    this->field = _field;

    this->field.init(this->x, x);
    this->field.init(this->y, y);

}

Point::Point(Field fld, Integer x, Integer y)
{
    this->field = fld;
    this->field.init(this->x, x);
    this->field.init(this->y, y);
}

bool Point::IsEqual(const Point &p1) const
{
   if (this->x == p1.x
           && this->y == p1.y
           && this->field == p1.field)
       return true;
   else
       return false;
}

 std::ostream & operator<<(std::ostream & Str, Point const & v) {
    Str<<"Point: " << "x: " << v.x << "; y: " << v.y;
  // print something from v to str, e.g: Str << v.getX();
  return Str;
}

