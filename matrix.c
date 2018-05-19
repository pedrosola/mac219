/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem funcoes para leitura, criacao e escrita de matrizes.
*/

#include "matrix.h"

void printMatrix(double **M, uint64_t n, uint64_t m) {
    uint64_t i, j;
    for (i = 0; i < n; i++) {
        printf("| ");
        for (j = 0; j < m; j++) {
            printf("%.2f ", M[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

double **zeroMatrix(uint64_t n, uint64_t m) {
    uint64_t i;
    double **M = (double**) calloc(n, sizeof(double*));
    for (i = 0; i < n; i++) {
        M[i] = (double*) calloc(m, sizeof(double));
    }
    return M;
}

double **randMatrix(uint64_t n, uint64_t m, int seed) {
    uint64_t i, j;
    double **M = malloc(n * sizeof(double*));
    srand((unsigned) seed);
    for (i = 0; i < n; i++) {
        M[i] = malloc(m * sizeof(double));
        for (j = 0; j < m; j++) {
            M[i][j] = (double) rand();
        }
    }
    return M;
}

double **readMatrix(char *locale, uint64_t *n, uint64_t *m) {
    FILE *file = fopen (locale, "r");
    uint64_t i, j;
    double **M = zeroMatrix(*n, *m);;
    fscanf(file, "%lld", n);
    fscanf(file, "%lld", m);
    for (i = 0; i < *n; i ++) {
        for (j = 0; j < *m; j ++) {
            fscanf(file, "%lf", &M[i][j]);
        }
    }
    fclose(file);
    return M;
}

int writeMatrix(double **M, uint64_t n, uint64_t m, char *locale) {
    FILE *out = fopen (locale, "w");
    uint64_t i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j ++) {
            fprintf(out, "%f ", M[i][j]);
        }
        fprintf(out, "\n");
    }
    fclose (out);
    return 0;
}