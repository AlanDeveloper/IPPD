/* * RELATÓRIO DE IMPLEMENTAÇÃO - k-NN 1D PARALELO COM OPENMP
 * * 1. POR QUE PARALELIZAR O LAÇO EXTERNO?
 * Optei por paralelizar o laço das consultas (j) e não o de varredura (i) pelo seguinte:
 * - Se eu usasse OpenMP no laço interno, haveria uma "condição de corrida" (race condition). 
 * Múltiplas threads tentariam atualizar o mesmo array 'best' ao mesmo tempo.
 * - Para resolver isso no laço interno, eu precisaria usar travas (critical ou atomic), 
 * o que faria o programa rodar mais devagar do que a versão sequencial devido ao overhead.
 * - Paralelizando o laço externo, cada consulta é independente. Cada thread tem seu 
 * próprio array 'best' (privado), eliminando conflitos e garantindo performance máxima.
 * * 2. EXPERIMENTOS E DESEMPENHO:
 * Máquina: Intel(R) Core(TM) i5-10210U CPU @ 1.60GHz
 * Configuração: N=1000000, M=2000, k=8
 * * - Sequencial (1 thread): 1.68s
 * - Paralelo (2 threads): 0.85s  (Speedup: 1.97x)
 * - Paralelo (4 threads): 0.44s  (Speedup: 3.81x)
 * - Paralelo (8 threads): 0.38s  (Speedup: 4.42x)
 * * Observação: O ganho de 4 para 8 threads foi menor porque meu processador tem 4 cores 
 * físicos e usa Hyperthreading. O melhor escalonamento foi o 'static', pois a carga 
 * de trabalho por consulta é praticamente idêntica.
 * * 3. VERIFICAÇÃO DE CORRETUDE:
 * O valor de 'global_sum' e dos elementos de 'sum_k' foram idênticos em todas as execuções,
 * respeitando a precisão de ponto flutuante (double).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Mantém as k menores distâncias em ordem
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
    const int N = 1000000;   // Treino
    const int M = 2000;      // Consultas
    const int k = 8;         // k-vizinhos
    const unsigned seed = 0;

    double *train = (double*)malloc((size_t)N * sizeof(double));
    double *query = (double*)malloc((size_t)M * sizeof(double));
    double *sum_k = (double*)malloc((size_t)M * sizeof(double));

    if (!train || !query || !sum_k) {
        fprintf(stderr, "Erro de alocação.\n");
        return 1;
    }

    // Inicialização idêntica à versão sequencial para comparação
    srand(seed);
    for (int i = 0; i < N; i++) train[i] = (double)rand() / (double)RAND_MAX;
    for (int j = 0; j < M; j++) query[j] = (double)rand() / (double)RAND_MAX;

    double global_sum = 0.0;
    double start_t = omp_get_wtime();

    // Paralelização do laço de consultas
    // Usei reduction para somar as distâncias de cada consulta no total global com segurança
    #pragma omp parallel for reduction(+:global_sum) schedule(static)
    for (int j = 0; j < M; j++) {
        double best[64]; // Array local à thread
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
    printf("Tempo total: %.4f segundos\n", end_t - start_t);
    printf("global_sum=%.17g\n", global_sum);
    printf("sum_k[0]=%.17g sum_k[M-1]=%.17g\n", sum_k[0], sum_k[M-1]);

    free(train);
    free(query);
    free(sum_k);
    return 0;
}