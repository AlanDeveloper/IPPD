# Paralelização do k-NN 1D com OpenMP

Este projeto implementa o algoritmo k-NN (k-Nearest Neighbors) para busca de vizinhos próximos em uma dimensão, utilizando a biblioteca OpenMP para paralelização em processadores multi-core.

## Como Compilar

Certifique-se de ter o `gcc` instalado com suporte a OpenMP. No terminal, utilize os comandos abaixo:

```bash
# Compilar versão com escalonamento estático (padrão)
gcc -O3 -fopenmp knn_openmp.c -o knn_omp -lm

# Compilar versão com escalonamento dinâmico
gcc -O3 -fopenmp knn_dynamic.c -o knn_dyn -lm
```

## Como Executar

### Importante: Configuração do Número de Threads

Antes de executar, você **deve** definir a variável de ambiente `OMP_NUM_THREADS` para controlar quantas threads serão utilizadas na paralelização:
```bash
# Define o número de threads (exemplo: 4 threads)
export OMP_NUM_THREADS=4

# Executar o programa
./knn_omp
./knn_dyn