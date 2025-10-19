#include <stdio.h>
#include <stdlib.h>

// ============================================
// GUIA RÁPIDO: PONTEIROS EM C
// ============================================

// --------------------------------------------
// 1. CONCEITOS BÁSICOS: &, *, **
// --------------------------------------------
void exemplo_basico() {
    printf("\n=== CONCEITOS BÁSICOS ===\n");
    
    int x = 10;
    
    printf("x = %d\n", x);           // Valor de x: 10
    printf("&x = %p\n", &x);         // Endereço de x
    
    int *p = &x;                     // p guarda o endereço de x
    printf("p = %p\n", p);           // Endereço (igual a &x)
    printf("*p = %d\n", *p);         // Valor dentro do endereço: 10
    
    int **pp = &p;                   // pp guarda o endereço de p
    printf("pp = %p\n", pp);         // Endereço de p
    printf("*pp = %p\n", *pp);       // Valor dentro de pp (endereço de x)
    printf("**pp = %d\n", **pp);     // Valor dentro de x: 10
}

// --------------------------------------------
// 2. MODIFICAR VARIÁVEL COM PONTEIRO (*)
// --------------------------------------------
void dobra(int *n) {
    *n = *n * 2;  // Modifica o valor original
}

void exemplo_modificar_variavel() {
    printf("\n=== MODIFICAR VARIÁVEL ===\n");
    
    int x = 5;
    printf("Antes: x = %d\n", x);
    
    dobra(&x);  // Passa o ENDEREÇO de x
    printf("Depois: x = %d\n", x);  // x foi modificado para 10
}

// --------------------------------------------
// 3. ALOCAR MEMÓRIA COM PONTEIRO DUPLO (**)
// --------------------------------------------
void aloca_array(int **arr, int tamanho) {
    *arr = (int *)malloc(sizeof(int) * tamanho);
    
    // Preenche o array
    for (int i = 0; i < tamanho; i++) {
        (*arr)[i] = i + 1;
    }
}

void exemplo_alocacao() {
    printf("\n=== ALOCAÇÃO DE MEMÓRIA ===\n");
    
    int *lista = NULL;
    
    aloca_array(&lista, 5);  // Passa o ENDEREÇO do ponteiro
    
    printf("Array alocado: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
    
    free(lista);  // SEMPRE liberar memória!
}

// --------------------------------------------
// 4. LER ARRAY COM PONTEIRO SIMPLES (*)
// --------------------------------------------
int soma_array(int *arr, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += arr[i];  // Equivalente a: *(arr + i)
    }
    return soma;
}

void exemplo_leitura() {
    printf("\n=== LEITURA DE ARRAY ===\n");
    
    int nums[] = {1, 2, 3, 4, 5};
    int resultado = soma_array(nums, 5);
    
    printf("Soma: %d\n", resultado);
}

// --------------------------------------------
// 5. TROCA DE VALORES (SWAP)
// --------------------------------------------
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void exemplo_swap() {
    printf("\n=== TROCA DE VALORES ===\n");
    
    int x = 10, y = 20;
    printf("Antes: x=%d, y=%d\n", x, y);
    
    troca(&x, &y);
    printf("Depois: x=%d, y=%d\n", x, y);
}

// --------------------------------------------
// 6. ARITMÉTICA DE PONTEIROS
// --------------------------------------------
void exemplo_aritmetica() {
    printf("\n=== ARITMÉTICA DE PONTEIROS ===\n");
    
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;  // p aponta para arr[0]
    
    printf("*p = %d\n", *p);         // 10
    printf("*(p+1) = %d\n", *(p+1)); // 20
    printf("*(p+2) = %d\n", *(p+2)); // 30
    
    p++;  // p agora aponta para arr[1]
    printf("Após p++: *p = %d\n", *p);  // 20
}

// --------------------------------------------
// 7. COMPARAÇÃO: COM E SEM PONTEIRO
// --------------------------------------------
void sem_ponteiro(int n) {
    n = n * 2;  // Modifica apenas a CÓPIA
}

void com_ponteiro(int *n) {
    *n = *n * 2;  // Modifica o ORIGINAL
}

void exemplo_comparacao() {
    printf("\n=== COM vs SEM PONTEIRO ===\n");
    
    int x = 5;
    sem_ponteiro(x);
    printf("Após sem_ponteiro: x = %d\n", x);  // 5 (não mudou!)
    
    com_ponteiro(&x);
    printf("Após com_ponteiro: x = %d\n", x);  // 10 (mudou!)
}

// --------------------------------------------
// MAIN: EXECUTA TODOS OS EXEMPLOS
// --------------------------------------------
int main() {
    printf("╔════════════════════════════════════╗\n");
    printf("║  GUIA COMPLETO: PONTEIROS EM C    ║\n");
    printf("╚════════════════════════════════════╝\n");
    
    exemplo_basico();
    exemplo_modificar_variavel();
    exemplo_alocacao();
    exemplo_leitura();
    exemplo_swap();
    exemplo_aritmetica();
    exemplo_comparacao();
    
    printf("\n✅ Todos os exemplos executados!\n\n");
    
    return 0;
}