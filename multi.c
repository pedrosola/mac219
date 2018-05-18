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

double **parMultMatrix_p(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
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
    B11 = subMatrix(B, mB, 0, 0);
    B12 = subMatrix(B, mB, 0, mB1);
    B21 = subMatrix(B, mB, mA1nB1, 0);
    B22 = subMatrix(B, mB, mA1nB1, mB1);
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

double **parMultMatrix_o(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB) {
   return zeroMatrix (nA, mB);
}

/*

| a | b c | | g h | i |   | ag ah + bk+co bl+cp | ai + bm+cq |   | ag+bk+co ah+bl+cp | ai+bm+qc |
----------- ----------- = ------------------------------------ = -------------------------------- -----> bom
| d | e f | | k l | m |   | dg dh + ek+fo el+fp | di + em+fq |   | dg+ek+fo dh+el+fp | di+em+fq |
            | o p | q |

*/

/*

| a | b c | | g h | i |
----------- | k l | m | = submatrizes impossíveis de multiplicarem-se --------------------------- -----> ruim
| d | e f | -----------
            | o p | q |

*/
// conclusão mA1 = nB1
