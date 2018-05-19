/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem funcoes para multiplicacao de matriz.
*/

#include "multi.h"

double **subMatrix(double **M, uint64_t n, uint64_t i, uint64_t j) {
    uint64_t k;
    double **subM = malloc((n-i) * sizeof(double*));
    for(k = 0; k < n-i; k++) {
        subM[k] = &M[i+k][j];
    }
    return subM;
}

double **sumMatrix(double **A, double **B, uint64_t n, uint64_t m) {
    uint64_t i, j;
    double **C = malloc(n * sizeof(double*));
    for (i = 0; i < n; i++) {
        C[i] = malloc(m * sizeof(double));
        for (j = 0; j < m; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

double **multMatrix(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
    uint64_t i, j, k;
    double **C = zeroMatrix(nA, mB);
    for (i = 0; i < nA; i++) {
        for (j = 0; j < mB; j++) {
            for (k = 0; k < mAnB; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

double **parMultMatrix(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
    uint64_t i, j;
    double **A11, **A12, **A21, **A22,
           **B11, **B12, **B21, **B22,
           **C11, **C12, **C21, **C22, **C;
    uint64_t nA1, mA1nB1, mB1;
    nA1 = nA/2;
    mA1nB1 = mAnB/2;
    mB1 = mB/2;
    A11 = subMatrix(A, nA, 0, 0);
    A12 = subMatrix(A, nA, 0, mA1nB1);
    A21 = subMatrix(A, nA, nA1, 0);
    A22 = subMatrix(A, nA, nA1, mA1nB1);
    B11 = subMatrix(B, mAnB, 0, 0);
    B12 = subMatrix(B, mAnB, 0, mB1);
    B21 = subMatrix(B, mAnB, mA1nB1, 0);
    B22 = subMatrix(B, mAnB, mA1nB1, mB1);
    C11 = sumMatrix(multMatrix(A11, B11, nA1, mA1nB1, mB1), multMatrix(A12, B21, nA1, mAnB-mA1nB1, mB1), nA1, mB1);
    C12 = sumMatrix(multMatrix(A11, B12, nA1, mA1nB1, mB-mB1), multMatrix(A12, B22, nA1, mAnB-mA1nB1, mB-mB1), nA1, mB-mB1);
    C21 = sumMatrix(multMatrix(A21, B11, nA-nA1, mA1nB1, mB1), multMatrix(A22, B21, nA-nA1, mAnB-mA1nB1, mB1), nA-nA1, mB1);
    C22 = sumMatrix(multMatrix(A21, B12, nA-nA1, mA1nB1, mB-mB1), multMatrix(A22, B22, nA-nA1, mAnB-mA1nB1, mB-mB1), nA-nA1, mB-mB1);
    C = zeroMatrix(nA, mB);
    for (i = 0; i < nA1; i++) {
        for (j = 0; j < mB1; j++) {
            C[i][j] = C11[i][j];
        }
        for (j = mB1; j < mB; j++) {
            C[i][j] = C12[i][j-mB1];
        }
    }
    for (i = nA1; i < nA; i++) {
        for (j = 0; j < mB1; j++) {
            C[i][j] = C21[i-nA1][j];
        }
        for (j = mB1; j < mB; j++) {
            C[i][j] = C22[i-nA1][j-mB1];
        }
    }
    return C;
}

struct multArguments {
    int id;
    double ***c;
    double **A;
    double **B;
    uint64_t nA;
    uint64_t mAnB;
    uint64_t mB;
};

struct multArguments setMultArgs(int id, double ***c, double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
    struct multArguments *arg = malloc(sizeof(struct multArguments));
    arg->id = id;
    arg->c = c;
    arg->A = A;
    arg->B = B;
    arg->nA = nA;
    arg->mAnB = mAnB;
    arg->mB = mB;
    return *arg;
}

/* Versao de multMatrix a ser executada em thread */
void *multMatrix_p(void *argPointer) {
    struct multArguments arg;
    uint64_t i, j, k;
    double **C;
    arg = *(struct multArguments*) argPointer;
    C =zeroMatrix(arg.nA, arg.mB);
    for (i = 0; i < arg.nA; i++) {
        for (j = 0; j < arg.mB; j++) {
            for (k = 0; k < arg.mAnB; k++) {
                C[i][j] += arg.A[i][k] * arg.B[k][j];
            }
        }
    }
    arg.c[arg.id] = C;
    return NULL;
}

double **parMultMatrix_p(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
    uint64_t i, j;
    int k;
    double **A11, **A12, **A21, **A22,
           **B11, **B12, **B21, **B22,
           **C11, **C12, **C21, **C22, **C;
    uint64_t nA1, mA1nB1, mB1;
    
    pthread_t thread[8];
    struct multArguments args[8];
    double **c[8];

    nA1 = nA/2;
    mA1nB1 = mAnB/2;
    mB1 = mB/2;
    A11 = subMatrix(A, nA, 0, 0);
    A12 = subMatrix(A, nA, 0, mA1nB1);
    A21 = subMatrix(A, nA, nA1, 0);
    A22 = subMatrix(A, nA, nA1, mA1nB1);
    B11 = subMatrix(B, mAnB, 0, 0);
    B12 = subMatrix(B, mAnB, 0, mB1);
    B21 = subMatrix(B, mAnB, mA1nB1, 0);
    B22 = subMatrix(B, mAnB, mA1nB1, mB1);

    args[0] = setMultArgs(0, c, A11, B11, nA1, mA1nB1, mB1);
    args[1] = setMultArgs(1, c, A12, B21, nA1, mAnB-mA1nB1, mB1);
    args[2] = setMultArgs(2, c, A11, B12, nA1, mA1nB1, mB-mB1);
    args[3] = setMultArgs(3, c, A12, B22, nA1, mAnB-mA1nB1, mB-mB1);
    args[4] = setMultArgs(4, c, A21, B11, nA-nA1, mA1nB1, mB1);
    args[5] = setMultArgs(5, c, A22, B21, nA-nA1, mAnB-mA1nB1, mB1);
    args[6] = setMultArgs(6, c, A21, B12, nA-nA1, mA1nB1, mB-mB1);
    args[7] = setMultArgs(7, c, A22, B22, nA-nA1, mAnB-mA1nB1, mB-mB1);

    for (k = 0; k < 8; k++) {
        if (pthread_create(&thread[k], NULL, multMatrix_p, &args[k])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    C = zeroMatrix(nA, mB);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    C11 = sumMatrix(c[0], c[1], nA1, mB1);
    for (i = 0; i < nA1; i++) {
        for (j = 0; j < mB1; j++) {
            C[i][j] = C11[i][j];
        }
    }
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    C12 = sumMatrix(c[2], c[3], nA1, mB-mB1);
    for (i = 0; i < nA1; i++) {
        for (j = mB1; j < mB; j++) {
            C[i][j] = C12[i][j-mB1];
        }
    }
    pthread_join(thread[4], NULL);
    pthread_join(thread[5], NULL);
    C21 = sumMatrix(c[4], c[5], nA-nA1, mB1);
    for (i = nA1; i < nA; i++) {
        for (j = 0; j < mB1; j++) {
            C[i][j] = C21[i-nA1][j];
        }
    }
    pthread_join(thread[6], NULL);
    pthread_join(thread[7], NULL);
    C22 = sumMatrix(c[6], c[7], nA-nA1, mB-mB1);
    for (i = nA1; i < nA; i++) {
        for (j = mB1; j < mB; j++) {
            C[i][j] = C22[i-nA1][j-mB1];
        }
    }
    return C;
}

double **parMultMatrix_o(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
   return zeroMatrix (nA, mB);
}