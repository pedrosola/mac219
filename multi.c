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

void writeSubMatrix(double **M, double **subM, uint64_t i0, uint64_t I, uint64_t j0, uint64_t J) {
    uint64_t i, j;
    for (i = i0; i < I; i++) {
        for (j = j0; j < J; j++) {
            M[i][j] = subM[i-i0][j-j0];
        }
    }
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
    C = zeroMatrix(nA, mB);

    C11 = sumMatrix(multMatrix(A11, B11, nA1, mA1nB1, mB1), multMatrix(A12, B21, nA1, mAnB-mA1nB1, mB1), nA1, mB1);
    C12 = sumMatrix(multMatrix(A11, B12, nA1, mA1nB1, mB-mB1), multMatrix(A12, B22, nA1, mAnB-mA1nB1, mB-mB1), nA1, mB-mB1);
    C21 = sumMatrix(multMatrix(A21, B11, nA-nA1, mA1nB1, mB1), multMatrix(A22, B21, nA-nA1, mAnB-mA1nB1, mB1), nA-nA1, mB1);
    C22 = sumMatrix(multMatrix(A21, B12, nA-nA1, mA1nB1, mB-mB1), multMatrix(A22, B22, nA-nA1, mAnB-mA1nB1, mB-mB1), nA-nA1, mB-mB1);

    writeSubMatrix(C, C11, 0, nA1, 0, mB1);
    writeSubMatrix(C, C12, 0, nA1, mB1, mB);
    writeSubMatrix(C, C21, nA1, nA, 0, mB1);
    writeSubMatrix(C, C22, nA1, nA, mB1, mB);
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
    arg = *(struct multArguments*) argPointer;
    arg.c[arg.id] = multMatrix(arg.A, arg.B, arg.nA, arg.mAnB, arg.mB);
    return NULL;
}

double **parMultMatrix_p(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
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
    C = zeroMatrix(nA, mB);

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
            return 0;
        }
    }
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    C11 = sumMatrix(c[0], c[1], nA1, mB1);
    writeSubMatrix(C, C11, 0, nA1, 0, mB1);
    
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    C12 = sumMatrix(c[2], c[3], nA1, mB-mB1);
    writeSubMatrix(C, C12, 0, nA1, mB1, mB);
    
    pthread_join(thread[4], NULL);
    pthread_join(thread[5], NULL);
    C21 = sumMatrix(c[4], c[5], nA-nA1, mB1);
    writeSubMatrix(C, C21, nA1, nA, 0, mB1);
    
    pthread_join(thread[6], NULL);
    pthread_join(thread[7], NULL);
    C22 = sumMatrix(c[6], c[7], nA-nA1, mB-mB1);
    writeSubMatrix(C, C22, nA1, nA, mB1, mB);
    
    return C;
}

struct sumMultArguments {
    int id;
    double **C;
    uint64_t nC;
    uint64_t mC;
    struct multArguments args[2];
};

struct sumMultArguments setSumMultArgs(int id, double **C, uint64_t nC, uint64_t mC, struct multArguments arg0, struct multArguments arg1) {
    struct sumMultArguments *arg = malloc(sizeof(struct sumMultArguments));
    arg->id = id;
    arg->C = C;
    arg->nC = nC;
    arg->mC = mC;
    arg->args[0] = arg0;
    arg->args[1] = arg1;
    return *arg;
}

void *sumMultMatrix_p(void *argPointer) {
    int index;
    uint64_t n, m, N, M;
    double **C_, ***c;
    struct sumMultArguments arg;
    arg = *(struct sumMultArguments*) argPointer;
    c = arg.args[0].c;
    n = arg.args[0].nA;
    m = arg.args[0].mB;
    N = arg.nC;
    M = arg.mC;
    index = 2*arg.id;
    multMatrix_p(&arg.args[0]);
    multMatrix_p(&arg.args[1]);
    C_ = sumMatrix(c[index], c[index+1], n, m);

    if (arg.id == 0) {
        writeSubMatrix(arg.C, C_, 0, n, 0, m);
    }
    if (arg.id == 1) {
        writeSubMatrix(arg.C, C_, 0, n, M-m, M);
    }
    if (arg.id == 2) {
        writeSubMatrix(arg.C, C_, N-n, N, 0, m);
    }
    if (arg.id == 3) {
        writeSubMatrix(arg.C, C_, N-n, N, M-m, M);
    }
    return NULL;
}

double **parMultMatrix_p2(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
    int k;
    double **A11, **A12, **A21, **A22,
           **B11, **B12, **B21, **B22,
           **C;
    uint64_t nA1, mA1nB1, mB1;
    
    pthread_t thread[4];
    struct sumMultArguments sArgs[4];
    struct multArguments mArgs[8];
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
    C = zeroMatrix(nA, mB);

    mArgs[0] = setMultArgs(0, c, A11, B11, nA1, mA1nB1, mB1);
    mArgs[1] = setMultArgs(1, c, A12, B21, nA1, mAnB-mA1nB1, mB1);
    mArgs[2] = setMultArgs(2, c, A11, B12, nA1, mA1nB1, mB-mB1);
    mArgs[3] = setMultArgs(3, c, A12, B22, nA1, mAnB-mA1nB1, mB-mB1);
    mArgs[4] = setMultArgs(4, c, A21, B11, nA-nA1, mA1nB1, mB1);
    mArgs[5] = setMultArgs(5, c, A22, B21, nA-nA1, mAnB-mA1nB1, mB1);
    mArgs[6] = setMultArgs(6, c, A21, B12, nA-nA1, mA1nB1, mB-mB1);
    mArgs[7] = setMultArgs(7, c, A22, B22, nA-nA1, mAnB-mA1nB1, mB-mB1);

    sArgs[0] = setSumMultArgs(0, C, nA, mB, mArgs[0], mArgs[1]);
    sArgs[1] = setSumMultArgs(1, C, nA, mB, mArgs[2], mArgs[3]);
    sArgs[2] = setSumMultArgs(2, C, nA, mB, mArgs[4], mArgs[5]);
    sArgs[3] = setSumMultArgs(3, C, nA, mB, mArgs[6], mArgs[7]);
    
    for (k = 0; k < 4; k++) {
        if (pthread_create(&thread[k], NULL, sumMultMatrix_p, &sArgs[k])) {
            fprintf(stderr, "Error creating thread\n");
            return 0;
        }
    }
    for (k = 0; k < 4; k++) {
        pthread_join(thread[k], NULL);
    }
    return C;
}

double **parMultMatrix_o(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
   return zeroMatrix (nA, mB);
}