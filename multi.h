/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Header File -------------------
    Este arquivo contem os prototipos de funcao de multiplicao de matrizes.
*/

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "matrix.h"

/* Devolve a submatriz de A[n, :] com origem em (i,j). */
double **subMatrix(double **M, uint64_t n, uint64_t i, uint64_t j);

/* Devolve uma matriz que eh a soma das matrizes A[n, m] e B[n, m]. */
double **sumMatrix(double **A, double **B, uint64_t n, uint64_t m);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB]. */
double **multMatrix(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB].
 * Utiliza pthreads para calcular partições da matriz e depois as reune na matriz final. */
double **parMultMatrix_p(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB]. */
double **parMultMatrix_o(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);