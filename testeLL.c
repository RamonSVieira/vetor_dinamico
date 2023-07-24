#include "linked_list_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct list;

int main()
{
    time_t inicio, fim;
    int n, i, x;
    struct list *l01 = linked_list_create();
    scanf("%d", &n);
    inicio = time(0);

    for (i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        linked_list_push_back(l01, x);
    }

    fim = time(0);
    double tempo_segundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;

    // Exibindo o tempo em segundos com quatro casas decimais
    printf("Tempo de execucao: %.4lf segundos.\n", tempo_segundos);
    printf("Tamanho do vetor: %lu\n", (unsigned long)list_size(l01)); // Use "%lu" para size_t
    // print_list(l01);

    tempo_segundos = 0;

    inicio = time(0);
    linked_list_push_at(l01, 1, 999999);
    fim = time(0);
    tempo_segundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;

    // Exibindo o tempo em segundos com quatro casas decimais
    printf("Tempo de execucao: %.4lf segundos.\n", tempo_segundos);
    printf("Tamanho do vetor: %lu\n", (unsigned long)list_size(l01)); // Use "%lu" para size_t
    // print_list(l01);

    destroy_list(l01);
    return 0;
}
