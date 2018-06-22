/*  ------------------ EP 2 MAC0219 ------------------
    Authors: Pedro Sola Pimentel    NUSP 9298079
             Yannick Thomas Messias NUSP 8803834

    ------------------ Source File -------------------
    Este arquivo contem os prototipos de funcao de reducao de matrizes
    3x3
*/
/* devolve uma matriz M[3,3] em forma de vetor resultante da reducao
da lista de matrizes em mList, sem otimizacoes */
int *reduction_c(int **mList, int lsize);

/* devolve uma matriz M[3,3] em forma de vetor resultante da reducao
da lista de matrizes em mList, utlizando CUDA */
int *reduction_p(int **mList, int lsize);

/* Recebe um vetor V[asize] e delve o maximo do vetor, utilizando reducao
em CUDA */
int reduction_max(int *data, int asize);
