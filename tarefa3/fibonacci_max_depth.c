#include <stdio.h>
#include <omp.h>

long long fib_seq(int n) {
    if (n < 2)
        return n;
    return fib_seq(n - 1) + fib_seq(n - 2);
}

long long fib(int n, int depth) {
    if (n < 2)
        return n;

    if (depth <= 0) {
        return fib_seq(n);
    }

    long long x, y;

    #pragma omp task shared(x) firstprivate(n, depth)
    x = fib(n - 1, depth - 1);

    #pragma omp task shared(y) firstprivate(n, depth)
    y = fib(n - 2, depth - 1);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 20;
    int max_depth = 10;
    long long result;
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n, max_depth);
    }

    double end = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Tempo de execução: %.6f segundos\n", end - start);

    return 0;
}