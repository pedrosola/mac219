/* ------------------ EP 1 MAC0219 ------------------
   Authors: Pedro Sola Pimentel NUSP 9298079
            Yannick Thomas Messias NUSP 8803834

   ------------------ Header File -------------------
   Este arquivo contem os prototipos de funcao de multiplicao de matrizes.
*/

/* Recebe matrizes A[m, p] e B[p, n] e devolve uma matriz R[m, n] com o
resultado da multiplicao */
double **matMult_1 (double **A, double **B, int m, int p, int n) ;

/* Aloca uma matriz M[n][m] de floats com precisao dupla e a retorna */
double **allocMatrix (int n, int m) ;
