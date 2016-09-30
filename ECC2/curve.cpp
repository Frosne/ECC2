#include "curve.h"
#include "algorithms.h"
#include <iostream>

Curve::Curve(Integer field)
{
    this->field = Modular<Integer> (field);
    this->IsWeierstrassForm = false;
}

Curve::Curve(Integer field, Integer a, Integer b)
{
    this->field = Modular<Integer>(field);
    this->field.init(this->a1,Integer(0));
    this->field.init(this->a2,Integer(0));
    this->field.init(this->a3,Integer(0));
    this->field.init(this->a4,a);
    this->field.init(this->a6,b);
    this->IsWeierstrassForm = true;
}

Curve::Curve(Integer field, int a, int b)
{
    this->field = Modular<Integer>(field);
    this->field.init(this->a1,Integer(0));
    this->field.init(this->a2,Integer(0));
    this->field.init(this->a3,Integer(0));
    this->field.init(this->a4,Integer(a));
    this->field.init(this->a6,Integer(b));
    this->IsWeierstrassForm = true;

}

Curve::Curve(Integer field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6)
{
    this->field = Modular<Integer>(field);
    this->field.init(this->a1, a1);
    this->field.init(this->a2, a2);
    this->field.init(this->a3, a3);
    this->field.init(this->a4, a4);
    this->field.init(this->a6, a6);
    this->IsWeierstrassForm = false;
}

Curve::Curve(Field field)
{
    this->field = field;
}

Curve::Curve(Field field, int a, int b)
{
    this->field = field;
    this->field.init(this->a2,Integer(0));
    this->field.init(this->a3,Integer(0));
    this->field.init(this->a4,a);
    this->field.init(this->a6,b);
    this->IsWeierstrassForm = true;
}

Curve::Curve(Field field, Integer a, Integer b)
{
    this->field = Modular<Integer>(field);
    this->field.init(this->a1,Integer(0));
    this->field.init(this->a2,Integer(0));
    this->field.init(this->a3,Integer(0));
    this->field.init(this->a4,a);
    this->field.init(this->a6,b);
    this->IsWeierstrassForm = true;
}

Curve::Curve(Field field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6)
{
    this->field = field;
    this->field.init(this->a1, a1);
    this->field.init(this->a2, a2);
    this->field.init(this->a3, a3);
    this->field.init(this->a4, a4);
    this->field.init(this->a6, a6);
    this->IsWeierstrassForm = false;
}

Integer Curve::ComputeDiscriminant()
{
    // - 16 (4 a ^3 + 27 b ^ 2)
    Integer d = -16 * (4 * (this->a4 * this->a4  * this->a4  ) + 27 * (this->a6 * this->a6) );
    this->discriminant = d;
    return d;
}

bool Curve::IsSingular()
{
    Integer discriminant = this->ComputeDiscriminant();
    return discriminant == Integer(0);
}

bool Curve::IsPointOnCurve(Point p)
{
    Integer x = p.x;
    Integer y = p.y;

    Field::Element x3, x2, y2,temp, temp2, zero;
    field.init(zero,0);

    x3 = Algorithms::power(field,x,3);
    x2 = Algorithms::power(field,x,2);
    y2 = Algorithms::power(field,y,2);

    if (this->IsWeierstrassForm)
    {
        temp = field.mul(temp,this->a4,x);
        temp = field.add(temp,temp,this->a6);
        temp = field.add(temp,temp,x3);
        temp = field.sub(temp,y2,temp);
        if (temp == zero)
            return true;
        else return false;
    }
    else
    {
        temp = field.mul(temp,x,y);
        temp = field.mul(temp,temp,this->a1);
        temp = field.add(temp, temp, y2);
        // now in temp2 y^2 + a1xy
        temp = field.add(temp,temp,this->a3);
        temp = field.sub(temp, temp, x3);
        temp2 = field.mul(temp2,this->a2, x2);
        temp = field.sub(temp,temp,temp2);
        temp2 = field.mul(temp2,x,this->a4);
        temp = field.sub(temp, temp, temp2);
        temp = field.sub(temp, temp, this->a6);
        if (temp == zero)
            return true;
        else return false;
    }

}

Integer Curve::ComputeYFromX(Field::Element & result, Integer x)
{
    Field::Element x3, temp, y2;
    if (this->IsWeierstrassForm)
    {
       x3 = Algorithms::power(this->field,x,3);
       this->field.mul(temp, x, this->a4);
       this->field.add(temp, x3, temp);
       this->field.add(temp, temp, this->a6);
       y2 = temp;
    }

  return Algorithms::SquareRoot(result, this->field,y2);
}

Point Curve::PointAddition(Point p, Point q)
{
    Field::Element lambda,temp, temp1, temp2;
    Field::Element lambda2,x3,y3;

    lambda = this->field.div(lambda, (this->field.sub(temp1, q.y, p.y)),(this->field.sub(temp2, q.x, p.x)));
    this->field.mul(lambda2, lambda, lambda);
    this->field.add(temp, lambda2, this->field.mul(temp2, this->a1, lambda));
    this->field.sub(temp, temp, this->a2);
    this->field.sub(temp, temp, p.x);
    this->field.sub(x3, temp, q.x);

    //y3 is equal to 0
    this->field.sub(y3, y3, p.y);
    this->field.sub(temp, x3, p.x);
    this->field.mul(temp, temp, lambda);
    this->field.sub(y3, y3, temp);
    this->field.mul(temp, this->a1, x3);
    this->field.sub(y3, y3, temp);
    this->field.sub(y3, y3, this->a2);

    return Point(this->field, x3, y3);

}

Point Curve::PointDoubling(Point p)
{
    Field::Element temp1, temp2, x2;
    Field::Element x3, y3;

    x2 = Algorithms::power(this->field, p.x,2);
    this->field.mul(temp1, 3, x2);
    this->field.add(temp1, temp1, 2);
    this->field.mul(temp2, p.y, 2);
    this->field.div(temp1, temp1, temp2);

    this->field.mul(temp2, temp1, temp1);
    this->field.sub(x3,temp2, p.x );
    this->field.sub(x3, x3, this->a4);

    this->field.sub(temp2, p.x, x3);
    this->field.mul(y3, temp1, temp2);
    this->field.sub(y3, y3, p.y);

    return Point(this->field, x3, y3);


}

Point Curve::PointSummary(Point p, Point q)
{
    if (p.IsEqual(q))
    {
       return this->PointDoubling(p);
    }
    else
       return this->PointAddition(p,q);
}



std::ostream & operator<<(std::ostream & Str, Curve const & c) {
    if (c.a1 == 0 && c.a2 == 0 && c.a3 == 0 )
        Str<<"Curve is in Weierstrass form: " << "y^2=x^3 + " << c.a4 << "x + " <<c.a6 <<"; "<<std::endl;
    else
        Str<<"Curve is not in Weierstrass form: " << "y^2 + " << c.a1<< "xy + " <<c.a3 << "y = x^3 + " <<c.a2 << "x^2 + " << c.a4 << "x + " << c.a6 <<std::endl;
    return Str;
}
