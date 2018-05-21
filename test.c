#include "matrix.h"
#include "multi.h"

int main (int argc, char **argv) {
    double **A, **B, **C;
    uint64_t n, m;
    A = randMatrix (64, 64, 10);
    B = randMatrix (64, 64, 10);

    writeMatrix (A, 64, 64, "sample/a");
    writeMatrix (B, 64, 64, "sample/b");

    A = readMatrix ("sample/a", &n, &m);
    printf ("%ld %ld\n", n, m);

    C = parMultMatrix (A, B, n, m, n);
    return 0;
}
