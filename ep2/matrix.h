/*  ------------------ EP 2 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem os prototipos de funcao de leitura e escrita
    de matrizes.
*/

#include <stdlib.h>
#include <stdio.h>

/* Imprime a matrix M[n, m] na saida padrao */
void printMatrix(int *M);

/* Devolve uma matriz M[9, n] composta por numeros aleatorios
 * inteiros, utilizando a semente "seed". */
int **randMatrix(int n, int seed);

/* Devolve uma lista de matrizes mList[n] lida do arquivo localizado em locale */
int **readMatrixList(char *locale, int *lsize);

/* Escreve a lista de matrizes mList[n] no arquivo localizado em locale. */
int writeMatrixList (char *local, int ***mList, int lsize);
