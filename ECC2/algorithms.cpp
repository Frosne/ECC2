#include "algorithms.h"
#include <curve.h>

Algorithms::Algorithms()
{

}

Integer Algorithms::power(Integer number, int power)
{
    if (power < 1)
            return number;
    int counter = 1;
    Integer result = number;
    while (counter < power)
    {
       result = result.mul(result,result, number);
       counter ++;

    }
    return result;
}

Integer Algorithms::power(Field fld, Integer number, int power)
{
    if (power <1)
        return number;
    int counter = 1;
    Integer result = number;
    while(counter< power)
    {
        result = fld.mul(result,result, number);
        counter ++;
    }
    return result;
}

Points Algorithms::ComputeAllPointsOnCurve(Field fld, Curve c)
{
   Points lst;
   Field::Element y;
   for (int i = 0; i<=fld.maxElement(); i++)
   {
       if (c.ComputeYFromX(y,i) == Integer::zero)
       {
           lst.push_back(Point(c.field,Integer(i),Integer(y)));
       }
   }

   return lst;

}

Integer Algorithms::SquareRoot(Field::Element & result, Field fld, Integer element)
{
    Field::Element temp;
    for (Integer i = 0; i<=fld.maxElement(); i++)
    {
        fld.mul(temp, i,i);
        if (temp == element)
        {
            result = i;
            return Integer::zero;
        }

    }
    return Integer::mOne;
}
