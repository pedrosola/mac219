/* ------------------ EP 1 MAC0219 ------------------
   Authors: Pedro Sola Pimentel    NUSP 9298079
            Yannick Thomas Messias NUSP 8803834

   ------------------  Main File  -------------------
   Neste Arquivo estao: leitura de argumentos e chamadas de funcoes.

*/

#include <stdio.h>
#include <stdlib.h>
#include "multi.h" /* Funcoes de multiplicao de matrizes */
#include "matrix.h" /* Funcoes de leitura e escrita de matrizes */

int main (int argc, char **argv) {
   double **A, **B, **R;
   uint64_t i, j, n, m, k, l;
   char I;

   I = (char) argv[1];
   A = readMatrix (argv[2], &n, &m);
   B = readMatrix (argv[3], &k, &l);

   if (argc < 4) {
      printf ("Usage:\n \t.\\main <implementation> <path_to_m1> <path_to_m2> <path_to_m3> ");
      return 0;
   }
   else if (m != k) {
      printf ("Matrix dimensions don't match\n");
      return 0;
   }

   if (I == 'p') {
      printf ("Calculando resultado utilizando pthreads ...");
      R = parMultMatrix_p (A, B, n, m, l);
   } else if (I == 'o') {
      printf ("Calculando resultado utilizando OpenMP ...");
      R = parMultMatrix_o (A, B, n, m, l);

   } else
      R = multMatrix (A, B, n, m, l);

   for (i = 0; i < n; i++) {
      for (j = 0; j < l; j++) {
         printf (" %f", R[i][j]);
      }
      printf ("\n");
   }
   writeMatrix (R, n, l, argv[3]);
   printf("Resultado escrito em %s\n", argv[3]);
   return 0;

}
