#include "solution.h"

#include <omp.h>

FLOAT_TYPE
compute_sin_on_gpu() {
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

int main() {

  double t1 = omp_get_wtime();
  FLOAT_TYPE sin_sum_gpu = compute_sin_on_gpu();
  double elapsed_time = omp_get_wtime() - t1;

  printf("cpu;%lu;%s;%f;%e\n", ARRAY_SIZE, XSTR(FLOAT_TYPE), elapsed_time, sin_sum_gpu);
}

