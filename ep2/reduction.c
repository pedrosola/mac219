/*  ------------------ EP 2 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------  Main File  -------------------
    Neste Arquivo estao: leitura de argumentos e chamadas de funcoes.
*/

#include "reduction.h"
#include <stdlib.h>

int *reduction_c(int **mList, int lsize) {
   int *max = (int*) calloc(9, sizeof (int));
   int i, j;

   for (i = 0; i < 9; i++)
      for (j = 0; j < lsize; j++)
         if (mList[i][j] > max[i])
            max[i] = mList[i][j];

   return max;
}

int *reduction_p(int **mList, int lsize) {
   int *max = (int*) calloc(9, sizeof (int));
   int i;
   for (i = 0; i < 9; i++)
      max[i] = reduction_max(mList[i], lsize);
   return max;
}
int reduction_max(int *data, int asize) {
   //CUDA MAX REDUCTION HERE
   return 0;
}
