#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10;
    int a_seq[10];
    int a_par[10];

    // Valor inicial
    a_seq[0] = 5;
    a_par[0] = 5;

    // -------------------------------
    // Versão SEQUENCIAL (dependente)
    // -------------------------------
    for (int i = 1; i < N; i++) {
        a_seq[i] = a_seq[i - 1] + 2;
    }

    // -------------------------------
    // Versão PARALELIZÁVEL (forma fechada)
    // -------------------------------
    #pragma omp parallel for
    for (int i = 1; i < N; i++) {
        a_par[i] = a_par[0] + 2 * i;
    }

    // -------------------------------
    // Exibe os resultados
    // -------------------------------
    printf("i\tSequencial\tParalelo\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t\t%d\n", i, a_seq[i], a_par[i]);
    }

    return 0;
}
