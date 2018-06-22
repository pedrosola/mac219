#include "matrix.h"
#include "reduction.h"
#include <sys/time.h>

int main (int argc, char **argv) {
   int n;
   int **M, *res;
   struct timeval t1, t2;
   double elapsedTime;

   if (argc == 2) {
      n = (int) argv[1];
      M = randMatrix(n, 10);

      gettimeofday(&t1, NULL);
      res = reduction_c(M, n);
      gettimeofday(&t2, NULL);
      elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
      elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
      printf("PROCESSOR TIME:\t%f ms\n", elapsedTime);

      gettimeofday(&t1, NULL);
      res = reduction_p(M, n);
      gettimeofday(&t2, NULL);
      elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
      elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
      printf("CUDA TIME:\t%f ms\n", elapsedTime);

   } else if (argc == 3) {
      n = (int) argv[1];
   } else {
      printf("Usage: ./test <n> --o");
   }
    printf("criando matrizes...\n");
    return 0;
}
