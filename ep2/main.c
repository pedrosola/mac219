/*  ------------------ EP 2 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------  Main File  -------------------
    Neste Arquivo estao: leitura de argumentos e chamadas de funcoes.
*/

#include <sys/time.h>
#include "matrix.h" /* Funcoes de leitura e escrita de matrizes */
#include "reduction.h" /*Funcoes de reducao de matriz */

int main(int argc, char **argv) {
   // clock_t start, diff;
   int **mList, lsize, *mRed;

   if (argc < 2) {
      printf("Usage:\n \t./main <path_to_matrix_list>\n\n");
      return 0;
   }

   mList = readMatrixList(argv[1], &lsize);
   mRed = reduction_c(mList, lsize);
   printMatrix(mRed);
   return 0;
}
