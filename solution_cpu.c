#include "solution.h"

#include <omp.h>

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

int main() {
  FLOAT_TYPE sin_sum_cpu = 0;
  double t1, t2;
  double elapsed_time = INFINITY;
  for (int attempt = 0; attempt < 5; ++attempt) {
    t1 = omp_get_wtime();
    sin_sum_cpu = compute_sin_on_cpu();
    t2 = omp_get_wtime() - t1;
    if (t2 < elapsed_time) {
      elapsed_time = t2;
    }
  }

  printf("cpu;%lu;%s;%f;%e\n", ARRAY_SIZE, XSTR(FLOAT_TYPE), elapsed_time, sin_sum_cpu);
}
