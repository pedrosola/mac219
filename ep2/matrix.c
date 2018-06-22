/*  ------------------ EP 2 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem funcoes para leitura, criacao e escrita de matrizes.
*/

#include "matrix.h"

void printMatrix(int *M) {
   int i, j;
   printf ("\n");
   for (i = 0; i < 3; i++) {
      printf("| ");
      for (j = 0; j < 3; j++)
         printf("%d ", M[i*j]);
      printf("|\n");
   }
   printf("\n");
}

int **randMatrix(int n, int seed) {
   int i, j;
   int **M = malloc(9 * sizeof(int*));
   srand((unsigned) seed);
   for (i = 0; i < 9; i++) {
      M[i] = malloc(n * sizeof(int));
      for (j = 0; j < n; j++)
         M[i][j] = (int) rand();
   }
   return M;
}

int **readMatrixList(char *locale, int *lsize) {
   FILE *file = fopen (locale, "r");
   int **M;
   int i, j;
   char temp[3];

   fscanf(file, "%d", lsize);
   fscanf(file, "%s", temp);
   printf ("%s %d", temp, *lsize);

   M = malloc(9 * sizeof(int*));
   for (i = 0; i < 9; i++)
      M[i] = malloc(*lsize * sizeof(int));

   for (i = 0; i < *lsize; i++) {
      for (j = 0; j < 9; j ++) {
         fscanf(file, "%d", &M[j][i]);
         printf("%d ", M[j][i]);
      } printf("\n");
      fscanf(file, "%s", temp);
   }

   fclose(file);
   return M;
}

int writeMatrixList (char *locale, int ***mList, int lsize) {
   FILE *out = fopen (locale, "w");
   int i, j, k;
   fprintf(out, "%d\n", lsize);
   fprintf(out, "*** \n");
   for (i = 0; i < lsize; i++) {
      for (j = 0; j < 3; j ++) {
         for (k = 0; j < 3; j ++) {
            fprintf(out, "%d ", mList[i][j][k]);
         } fprintf(out, "\n");
      } fprintf(out, "*** \n");
   } fclose(out);
   return 0;
}
