#include "matrix.h"
#include "multi.h"
#include <sys/time.h>

uint64_t Su64(const char *s) {
    uint64_t i;
    char c ;
    int scanned = sscanf(s, "%"SCNu64 "%c", &i, &c);
    if (scanned == 1) return i;
    if (scanned > 1) {
        /* TBD about extra data found */
        return i;
    }
    /* TBD failed to scan */  
    return 0;  
}

int main (int argc, char **argv) {
    double **A, **B;
    uint64_t n, m, o;
    struct timeval t1, t2;
    double elapsedTime;
    
    if (argc >= 4) {
        n = Su64(argv[1]);
        m = Su64(argv[2]);
        o = Su64(argv[3]);
    }
    else {
        printf("digite as dimensões de n, m e o:\n");
        scanf("%"SCNu64, &n);
        scanf("%"SCNu64, &m);
        scanf("%"SCNu64, &o);
        printf("\n");
    }
    printf("criando matrizes...\n");
    
    A = randMatrix(n, m, 1);
    writeMatrix(A, n, m, "a.sample");
    A = readMatrix("a.sample", &n, &m);
    printf("A[%ld, %ld]\n", n, m);
    
    B = randMatrix(m, o, 2);
    writeMatrix(B, m, o, "b.sample");
    B = readMatrix("b.sample", &m, &o);
    printf("B[%ld, %ld]\n", m, o);
    printf("\n");

    gettimeofday(&t1, NULL);
    multMatrix(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("standard:\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    parMultMatrix(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("partitioned:\t%f ms\n", elapsedTime);

    gettimeofday(&t1, NULL);
    ompMultMatrix(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("omp:\t\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    parMultMatrix_o(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("partitioned_o:\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    parMultMatrix_p(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("pthread_p:\t%f ms\n", elapsedTime);

    gettimeofday(&t1, NULL);
    parMultMatrix_p2(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("pthread_p2:\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    bestMultMatrix_o(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("best_o:\t\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    bestMultMatrix_p(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("best_p:\t\t%f ms\n", elapsedTime);
    
    gettimeofday(&t1, NULL);
    bestMultMatrix_p2(A, B, n, m, n);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("best_p2:\t%f ms\n", elapsedTime);
    
    printf("\n");
    
    return 0;
}
