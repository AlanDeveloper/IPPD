#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void pegaTamanhoVetor(int *n) {
    do {
        printf("\nDigite o total de números a serem somados: ");
        scanf("%d", n);
    } while (*n <= 0);
}

void pegaVetor(int **lista, int n) {
    *lista = (int *)malloc(sizeof(int) * n);
    if (*lista == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        (*lista)[i] = i + 1;
    }
}

long long somaSequencial(int *lista, int n) {
    long long soma = 0;
    for (int i = 0; i < n; i++) {
        soma += lista[i];
    }
    return soma;
}

long long somaParalela(int *lista, int n) {
    long long soma = 0;
    int inicio, fim, i, tid, nthreads, bloco;
    
    #pragma omp parallel reduction(+:soma) private(inicio, fim, i, tid, nthreads, bloco)
    {
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        bloco = n / nthreads;
        inicio = tid * bloco;
        fim = (tid == nthreads - 1) ? n : inicio + bloco;
        
        for (int i = inicio; i < fim; i++) {
            soma += lista[i];
        }
    }
    
    return soma;
}

int main() {
    int n = 0;
    int *lista = NULL;

    omp_set_num_threads(4);

    pegaTamanhoVetor(&n);
    pegaVetor(&lista, n);

    printf("\nTamanho do vetor: %d\n\n", n);
    
    // Soma SEQUENCIAL
    double inicio_seq = omp_get_wtime();
    long long resultado_seq = somaSequencial(lista, n);
    double fim_seq = omp_get_wtime();
    double tempo_seq = fim_seq - inicio_seq;
    
    printf("Soma sequencial:  %lld\n", resultado_seq);
    printf("Tempo sequencial: %.6f s\n\n", tempo_seq);
    
    // Soma PARALELA
    double inicio_par = omp_get_wtime();
    long long resultado_par = somaParalela(lista, n);
    double fim_par = omp_get_wtime();
    double tempo_par = fim_par - inicio_par;
    
    printf("Soma paralela:    %lld\n", resultado_par);
    printf("Tempo paralelo:   %.6f s\n\n", tempo_par);
    
    // Verificação e speedup
    printf("Resultados iguais? %s\n", (resultado_seq == resultado_par) ? "SIM" : "NÃO");
    printf("Speedup: %.2fx\n", tempo_seq / tempo_par);

    free(lista);
    return 0;
}