#ifndef SOLUTION_H
#define SOLUTION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#define STR(s) #s
#define XSTR(s) STR(s)

#define sin(x) _Generic((x), \
      long double: sinl, \
      double: sin, \
      float: sinf)(x)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE (100000000U)
#endif //  ARRAY_SIZE

#ifndef FLOAT_TYPE
#define FLOAT_TYPE double
#endif //  FLOAT_TYPE

#define TWO_PI (((FLOAT_TYPE) 2.0) * M_PI)
#define RADIAN_DIV (TWO_PI / (FLOAT_TYPE)(ARRAY_SIZE - 1))

#endif //  SOLUTION_H
