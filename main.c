/* ------------------ EP 1 MAC0219 ------------------
   Authors: Pedro Sola Pimentel NUSP 9298079
            Yannick Thomas Messias NUSP 8803834

   ------------------  Main File  -------------------
   Neste Arquivo estao as funcoes para manipulacao de matrizes,
   assim como leitura e escrita em arquivos.

*/

#include <stdio.h>
#include <stdlib.h>
#include "multi.h" /* Funcoes de Multiplicao de matrizes */

double **readMatrix (char *locale, int *n, int *m) {
   FILE *file = fopen (locale, "r");
   int i, j;
   double **M;
   fscanf (file, "%d", n);
   fscanf (file, "%d", m);

   M = allocMatrix (*n, *m);
   for (i = 0; i < *n; i ++)
      for (j = 0; j < *m; j ++)
         fscanf (file, "%lf", &M[i][j]);

   fclose (file);
   return M;
}

int writeMatrix (double **M, int n, int m, char *locale) {
   FILE *out = fopen (locale, "w");
   int i, j;

   for (i = 0; i < n; i++) {
      for (j = 0; j < m; j ++)
         fprintf (out, "%f ", M[i][j]);
      fprintf (out, "\n");
   }
   fclose (out);
   return 0;
}

int main (int argc, char **argv) {
   double **A, **B, **R;
   int i, j, n, m, k, l;
   A = readMatrix (argv[1], &n, &m);
   B = readMatrix (argv[2], &k, &l);

   if (m != k) {
      printf ("Matrix dimensions don't match\n");
      return 0;
   }

   R = matMult_1 (A, B, n, m, l);
   for (i = 0; i < n; i++) {
      for (j = 0; j < l; j++) {
         printf (" %f", R[i][j]);
      }
      printf ("\n");
   }
   writeMatrix (R, n, l, argv[3]);
   return 0;

}
