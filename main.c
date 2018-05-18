/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------  Main File  -------------------
    Neste Arquivo estao: leitura de argumentos e chamadas de funcoes.
*/

#include <stdio.h>
#include <stdlib.h>
#include "multi.h" /* Funcoes de multiplicao de matrizes */
#include "matrix.h" /* Funcoes de leitura e escrita de matrizes */

int main(int argc, char **argv) {
    double **A, **B, **C;
    uint64_t i, j, An, Am, Bn, Bm;
    char I;

    I = (char) argv[1];
    A = readMatrix(argv[2], &An, &Am);
    B = readMatrix(argv[3], &Bn, &Bm);

    if (argc < 4) {
        printf("Usage:\n \t.\\main <implementation> <path_to_m1> <path_to_m2> <path_to_m3>\n");
        return 0;
    }
    else if (Am != Bn) {
        printf("Matrix dimensions don't match\n");
        return 0;
    }
    if (I == 'p') {
        printf("Calculando resultado utilizando pthreads ...\n");
        C = parMultMatrix_p(A, B, An, Am, Bm);
    }
    else if (I == 'o') {
        printf("Calculando resultado utilizando OpenMP ...\n");
        C = parMultMatrix_o(A, B, An, Am, Bm);
    }
    else {
        C = multMatrix (A, B, An, Am, Bm);
    }
    for (i = 0; i < An; i++) {
        for (j = 0; j < Bm; j++) {
            printf(" %f", C[i][j]);
        }
        printf("\n");
    }
    writeMatrix(C, An, Bm, argv[3]);
    printf("Resultado escrito em %s\n", argv[3]);
    return 0;
}
