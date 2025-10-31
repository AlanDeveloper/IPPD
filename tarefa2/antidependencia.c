#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10;
    int b_seq[10];
    int b_par[10];
    int temp[10];

    // Inicializa os vetores
    for (int i = 0; i < N; i++) {
        b_seq[i] = i;
        b_par[i] = i;
    }

    // -------------------------------
    // Versão SEQUENCIAL (com antidependência)
    // -------------------------------
    for (int i = 0; i < N - 1; i++) {
        b_seq[i] = b_seq[i + 1] + 1;
    }

    // -------------------------------
    // Versão PARALELIZÁVEL (usando vetor temporário)
    // -------------------------------
    #pragma omp parallel for
    for (int i = 0; i < N - 1; i++) {
        temp[i] = b_par[i + 1] + 1;
    }

    // Copia o resultado para b_par
    for (int i = 0; i < N - 1; i++) {
        b_par[i] = temp[i];
    }

    // -------------------------------
    // Exibe os resultados
    // -------------------------------
    printf("i\tSequencial\tParalelo\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t\t%d\n", i, b_seq[i], b_par[i]);
    }

    return 0;
}
