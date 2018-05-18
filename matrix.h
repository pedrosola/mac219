/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem os prototipos de funcao de leitura e escrita
    de matrizes.
*/

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

/* Imprime a matrix M[n, m] na saida padrao */
void printMatrix(double **M, uint64_t n, uint64_t m);

/* Devolve uma matriz M[n, m] composta por zeros. */
double **zeroMatrix(uint64_t n, uint64_t m);

/* Devolve uma matriz M[n, m] composta por numeros aleatorios
 * inteiros (do tipo double), utilizando a semente "seed". */
double **randMatrix(uint64_t n, uint64_t m, int seed);

/* Devolve uma matriz M[n, m] lida do arquivo localizado em locale */
double **readMatrix(char *locale, uint64_t *n, uint64_t *m);

/* Escreve a Matriz M[n, m] no arquivo localizado em locale. */
int writeMatrix(double **M, uint64_t n, uint64_t m, char *locale);
