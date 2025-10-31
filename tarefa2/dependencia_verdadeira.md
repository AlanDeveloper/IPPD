🔍 Análise de dependência
1️⃣ Qual iteração produz o valor usado em a[i]?

A iteração i - 1 produz o valor que será lido pela iteração i, pois:

a[i] depende diretamente de a[i - 1].

2️⃣ É possível executar as iterações i e i - 1 ao mesmo tempo?

❌ Não.

A iteração i só pode começar depois que a iteração i - 1 terminou,
porque ela precisa do valor recém-calculado a[i - 1].

Isso é uma dependência verdadeira (Read After Write).

3️⃣ Este laço pode ser paralelizado diretamente com OpenMP?

❌ Não pode.

Se adicionarmos #pragma omp parallel for, várias iterações seriam executadas simultaneamente.

Isso quebraria a sequência de cálculos, já que a[i - 1] poderia ainda não ter sido atualizado quando a[i] fosse acessado.

O resultado seria incorreto ou indefinido.