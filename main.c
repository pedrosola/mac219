#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

float fu(int M, int k, double x) {
    return (sin((2*M + 1) * M_PI * x) * cos(2*M_PI*k*x)) / sin(M_PI*x);
}

int main (int argc, char *argv[]) {
    int N, k, M, i;
    double x, res = 0;
    double epsilon = pow(10, -320);
    
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    k = atoi(argv[3]);

    
    for (i = 0; i < N; i++) {
	x = (((double) rand()) / RAND_MAX) / 2;
	res += fu(M, k, x+epsilon);
    }

    res /= N;

    printf("%.10f\n",res);

    return 0;
    
}
