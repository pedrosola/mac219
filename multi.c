/* ------------------ EP 1 MAC0219 ------------------
   Authors: Pedro Sola Pimentel NUSP 9298079
            Yannick Thomas Messias NUSP 8803834

   ------------------ Source File -------------------
   Este arquivo contem funcoes para multiplicacao de matriz.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multi.h" /* Header File */

double **allocMatrix (int n, int m) {
   double **M = malloc (n * sizeof (double));
   int i;
   for (i = 0; i < n; i++) M[i] = malloc (m * sizeof (double));

   return M;
}

double **matMult_1 (double **A, double **B, int m, int n, int p) {
   double **R = allocMatrix (m, p);
   int i, j, k;

   for (i = 0; i < n; i++) {
      for (j = 0; j < p; j ++) {
         R[i][j] = 0;
         for (k = 0; k < n; k ++)
            R[i][j] += A[i][k] * B[k][j];
      }
   }
   return R;
}

 /*
int main (int argc, char *argc[]) {

   return 0;
}*/
