#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int N, M, k, T = 4;
double *v

float fu(int M, int k, double x) {
    return (sin((2*M + 1) * M_PI * x) * cos(2*M_PI*k*x)) / sin(M_PI*x);
}

void *func(void *thread_id) {
    int id = *(int*) thread_id;
    double x;
    int i, n = N/T;
    for (i = 0; i < n; i++)
        x = (((double) rand()) / RAND_MAX) / 2;
        v[id] += fu(M, k, x + epsilon);

    return NULL;
}

int main (int argc, char *argv[]) {
    int i, *thread_id, msec;
    pthread_t *f;
    clock_t start, diff;
    void* ret = NULL;
    double x, res = 0;
    double epsilon = pow(10, -320);
    
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    k = atoi(argv[3]);
    
    v = calloc(T, sizeof(double));
    thread_id = calloc(T, sizeof(int));
    f = malloc(T * sizeof(pthread_t));
    
    start = clock();
    
    for (i = 0; i < T; i++) {
        thread_id[i] = i;
        if (pthread_create(&f[i], NULL, func, &thread_id[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    for (i = 0; i < T; i++) {
        pthread_join(f[i], &ret);
    }
    for (i = 0; i < T; i++)
        res += v[i];
    res /= N;

    diff = clock() - start;
    
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Tempo na CPU com T threads: %d ms\n", msec);
    printf("Resultado: %.3f\n", res);
    
    start = clock();
    
    res = 0;
    for (i = 0; i < N; i++) {
        x = (((double) rand()) / RAND_MAX) / 2;
        res += fu(M, k, x + epsilon);
    }
    res /= N;
    
    diff = clock() - start;
    
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Tempo sequencial: %d ms\n", msec);
    printf("Resultado: %.3f\n", res);

    return 0;    
}