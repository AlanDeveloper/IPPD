#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10;
    int a[10] = { -1, 0, 4, -2, 3, 0, 5, -7, 8, -1 };
    int best_seq = -1;
    int best_par = -1;

    // -------------------------------
    // Versão SEQUENCIAL (original)
    // -------------------------------
    for (int i = 0; i < N; i++) {
        if (a[i] > 0) {
            best_seq = i;
        }
    }

    // -------------------------------
    // Versão PARALELIZÁVEL (com variável local por thread)
    // -------------------------------
    int nthreads;
    int local_best[100]; // suporte até 100 threads

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nt = omp_get_num_threads();
        local_best[tid] = -1;

        #pragma omp for
        for (int i = 0; i < N; i++) {
            if (a[i] > 0) {
                local_best[tid] = i; // guarda último positivo visto por esta thread
            }
        }
    }

    // Combinação determinística: pega o maior índice encontrado entre as threads
    best_par = -1;
    nthreads = omp_get_max_threads();
    for (int t = 0; t < nthreads; t++) {
        if (local_best[t] > best_par) {
            best_par = local_best[t];
        }
    }

    // -------------------------------
    // Exibe resultados
    // -------------------------------
    printf("Versão sequencial: best_idx = %d\n", best_seq);
    printf("Versão paralela  : best_idx = %d\n", best_par);

    return 0;
}
