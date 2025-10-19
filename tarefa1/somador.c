#include <stdio.h>
#include <stdlib.h>

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
        printf("Digite o número %d: ", i + 1);
        scanf("%d", &((*lista)[i]));
    }
}

int somaVetor(int *lista, int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += lista[i];
    }
    return soma;
}

int main() {
    int n = 0;
    int *lista = NULL;

    pegaTamanhoVetor(&n);
    pegaVetor(&lista, n);

    int resultado = somaVetor(lista, n);
    printf("Soma: %d\n", resultado);

    free(lista);
    return 0;
}