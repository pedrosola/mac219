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

/* Escreve na matriz M a submatriz sM nas posicoes de i0 ate I e j0 ate J. */
void writeSubMatrix(double **M, double **subM, uint64_t i0, uint64_t I, uint64_t j0, uint64_t J);

/* Devolve uma matriz que eh a soma das matrizes A[n, m] e B[n, m]. */
double **sumMatrix(double **A, double **B, uint64_t n, uint64_t m);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB]. */
double **multMatrix(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB].
 * Calcula o produto particionando as matrizes mas nao nenhuma paralelizacao ainda. */
double **parMultMatrix(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB].
 * Utiliza pthreads para calcular partições da matriz e depois as reune na matriz final. */
double **parMultMatrix_p(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB].
 * Utiliza pthreads para calcular partições da matriz e depois as reune na matriz final. */
double **parMultMatrix_p2(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);

/* Devolve uma matriz que eh o produto das matrizes A[nA, mA] e B[nB, mB]. */
double **parMultMatrix_o(double **A, double **B, uint64_t nA, uint64_t mAnB, uint64_t mB);