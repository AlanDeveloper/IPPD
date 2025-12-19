/* * Implementação k-NN com OpenMP - Estratégia Dynamic
 * * Testei o escalonamento dinâmico para ver se havia ganho com o balanceamento de carga.
 * No meu i5-10210U, o tempo foi muito similar ao static, já que cada consulta (M)
 * exige o mesmo esforço computacional (varrer N elementos).
 * * Verificação de corretude: Resultados de global_sum e sum_k batem 100% com o sequencial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

static inline void topk_insert(double *best, int k, double x) {
    if (x >= best[k - 1]) return;
    int pos = k - 1;
    while (pos > 0 && x < best[pos - 1]) {
        best[pos] = best[pos - 1];
        pos--;
    }
    best[pos] = x;
}

int main(void) {
    const int N = 1000000;
    const int M = 2000;
    const int k = 8;
    const unsigned seed = 0;

    double *train = (double*)malloc((size_t)N * sizeof(double));
    double *query = (double*)malloc((size_t)M * sizeof(double));
    double *sum_k = (double*)malloc((size_t)M * sizeof(double));

    if (!train || !query || !sum_k) {
        fprintf(stderr, "Erro de alocação.\n");
        return 1;
    }

    srand(seed);
    for (int i = 0; i < N; i++) train[i] = (double)rand() / (double)RAND_MAX;
    for (int j = 0; j < M; j++) query[j] = (double)rand() / (double)RAND_MAX;

    double global_sum = 0.0;
    double start_t = omp_get_wtime();

    // Versão com Escalonamento Dinâmico
    #pragma omp parallel for reduction(+:global_sum) schedule(dynamic)
    for (int j = 0; j < M; j++) {
        double best[64]; 
        for (int t = 0; t < k; t++) best[t] = INFINITY;

        const double q = query[j];
        for (int i = 0; i < N; i++) {
            double d = fabs(train[i] - q);
            topk_insert(best, k, d);
        }

        double s = 0.0;
        for (int t = 0; t < k; t++) s += best[t];
        sum_k[j] = s;
        global_sum += s;
    }

    double end_t = omp_get_wtime();

    printf("N=%d M=%d k=%d\n", N, M, k);
    printf("Tempo total (DYNAMIC): %.4f segundos\n", end_t - start_t);
    printf("global_sum=%.17g\n", global_sum);
    printf("sum_k[0]=%.17g sum_k[M-1]=%.17g\n", sum_k[0], sum_k[M-1]);

    free(train);
    free(query);
    free(sum_k);
    return 0;
}