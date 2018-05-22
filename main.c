/*  ------------------ EP 1 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             YnAnick Thomas Messias NUSP 8803834

    ------------------  Main File  -------------------
    Neste Arquivo estao: leitura de argumentos e chamadas de funcoes.
*/

#include <sys/time.h>
#include "multi.h" /* Funcoes de multiplicao de matrizes */
#include "matrix.h" /* Funcoes de leitura e escrita de matrizes */

int main(int argc, char **argv) {
    int msec;
    clock_t start, diff;
    double **A, **B, **C;
    uint64_t nA, mA, nB, mB;
    char I;

    I = (char) argv[1][0];
    A = readMatrix(argv[2], &nA, &mA);
    B = readMatrix(argv[3], &nB, &mB);

    if (argc < 5) {
        printf("Usage:\n \t.\\main <implementation> <path_to_m1> <path_to_m2> <path_to_m3>\n");
        return 0;
    }
    else if (mA != nB) {
        printf("Matrix dimensions don't match\n");
        return 0;
    }
    
    if (I == 'p') {
        printf("Calculando resultado utilizando pthreads...\n");
        start = clock();    
        C = parMultMatrix_p(A, B, nA, mA, mB);
        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Duração: %d ms\n", msec);
    }
    else if (I == 'o') {
        printf("Calculando resultado utilizando OpenMP...\n");
        start = clock();
        C = parMultMatrix_o(A, B, nA, mA, mB);
        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Duração: %d ms\n", msec);
    }
    else {
        printf("Calculando resultado tradicionalmente...\n");
        start = clock();
        C = multMatrix(A, B, nA, mA, mB);
        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Duração: %d ms\n", msec);
    }
    
    writeMatrix(C, nA, mB, argv[4]);
    printf("Resultado escrito em %s\n", argv[4]);
    
    return 0;
}
