#pragma once
#include <iostream>
#include <gmp.h>

#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>

using namespace Givaro;
typedef Modular<Integer> Field;

class MathObject {
public:
  //  virtual bool IsEqual(const MathObject& m1) const = 0;
    Field field;

};
