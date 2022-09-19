#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define sin(x) _Generic((x), \
      long double: sinl, \
      double: sin, \
      float: sinf)(x)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 100000000U
#endif //  ARRAY_SIZE

#ifndef FLOAT_TYPE
#define FLOAT_TYPE double
#endif //  FLOAT_TYPE

#define TWO_PI (((FLOAT_TYPE) 2.0) * M_PI)
#define RADIAN_DIV (TWO_PI / (FLOAT_TYPE)(ARRAY_SIZE - 1))

FLOAT_TYPE
compute_sin_on_cpu() {
  FLOAT_TYPE *sin_array;

  FLOAT_TYPE sin_sum = (FLOAT_TYPE) 0.0;
#pragma acc data create(sin_array[0:ARRAY_SIZE])
  {
#pragma acc kernels
    for (unsigned i = 0; i < ARRAY_SIZE; ++i) {
      sin_array[i] = sin(i * RADIAN_DIV);
    }

#pragma acc kernels loop reduction(+:sin_sum)
    for (unsigned i = 0; i < ARRAY_SIZE; ++i) {
      sin_sum += sin_array[i];
    }
  }


  return sin_sum;
}

FLOAT_TYPE
compute_sin_on_gpu() {
  FLOAT_TYPE *sin_array = (FLOAT_TYPE *)malloc(sizeof(FLOAT_TYPE) * ARRAY_SIZE);

  for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
    sin_array[i] = sin(i * RADIAN_DIV);
  }

  FLOAT_TYPE sin_sum = (FLOAT_TYPE) 0.0;
  for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
    sin_sum += sin_array[i];
  }

  free(sin_array);

  return sin_sum;
}

int main() {
  for (int i = 0; i < p)
  FLOAT_TYPE sin_sum_cpu = compute_sin_on_cpu();


  printf("%e\n", sin_sum);
}

