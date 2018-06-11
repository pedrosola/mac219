######### EP 1 MAC0219 ###########

Authors: Pedro Sola Pimentel
         Yannick Thomas Messias

Neste EP, deve ser construído um programa que lê e multiplica matrizes.
Utilizando as bibliotecas pthread e OpenMP.

Para compilar, utilize o comando make. Você deve garantir a presença das
bibliotecas OpenMP e pthread.

usage:
   ./main <implementacao> <path_to_m1> <path_to_m2> <path_to_m3>

where:
   m1 é um arquivo contendo uma matriz A (NxM)
   m2 é um arquivo contendo uma matriz B (MxO)
   m3 é um caminho valido no sistema.
   implementacao = p : pthreads
                   o : OpenMP
                   t : tradicional

para testes, use:
   ./test <N> <M> <O>
