/* ------------------ EP 1 MAC0219 ------------------
   Authors: Pedro Sola Pimentel    NUSP 9298079
            Yannick Thomas Messias NUSP 8803834

   ------------------ Source File -------------------
   Este arquivo contem os prototipos de funcao de leitura e escrita
   de matrizes.
*/

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/* Devolve uma matriz A (n, m) composta por zeros. */
double** zeroMatrix(uint64_t n, uint64_t m);

/* Devolve uma matriz A (n, m) composta por números aleatórios
   inteiros (do tipo double), utilizando a semente "seed". */
double** randMatrix(uint64_t n, uint64_t m, int seed);

/* Le uma matriz do arquivo localizado em locale e a devolve como uma
   matriz bidimensional A (n, m), armazenando o tamanho da matriz em m, n. */
double **readMatrix(char *locale, uint64_t *n, uint64_t *m) ;

/* Escreve a Matriz A (N,M) no arquivo localizado em locale. */
int writeMatrix(double **M, uint64_t n, uint64_t m, char *locale) ;
