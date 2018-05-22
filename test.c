#include "matrix.h"
#include "multi.h"
#include <sys/time.h>

int main (int argc, char **argv) {
    double **A, **B;
    uint64_t n, m;
    struct timeval t1, t2;
    double elapsedTime;
    
    A = randMatrix(1000, 1000, 10);
    B = randMatrix(1000, 1000, 10);

    writeMatrix(A, 1000, 1000, "sample/a");
    writeMatrix(B, 1000, 1000, "sample/b");

    A = readMatrix("sample/a", &n, &m);
    printf("%ld %ld\n", n, m);

    gettimeofday(&t1, NULL);
    multMatrix(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("standard:\t%f ms\n", elapsedTime);

    gettimeofday(&t1, NULL);
    ompMultMatrix (A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("omp:\t\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    parMultMatrix (A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("pthread:\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    parMultMatrix_p (A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("pthread_p:\t%f ms\n", elapsedTime);
    
    return 0;
}
