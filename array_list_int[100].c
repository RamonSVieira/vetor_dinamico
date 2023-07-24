#include "array_list_int.h"
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de dados
// a = Endereço de memória, size = Tamanho atual do vetor, capacity = Capacidade maxima atual
struct array_list_int
{
    int *a;
    unsigned int size, capacity;
};

/*
    ====================================================================================
    Aumentar a capacidade

    1° - Criar um novo ponteiro com o dobro da capacidade do antigo vetor
    2° - Iterar o nosso novo vetor adicionando os dados do antigo
    3° - Liberar a memória do antigo vetor
    4° - Atualizar o ponteiro para o nosso novo vetor
    5° - Atualizar a capacidade máxima do nosso novo vetor
    ====================================================================================
    Notação: O(N) Por cuasa da operação de cópia, irá executar n vezes, n sendo o ${size} do vetor;
*/
int increase_capacity(array_list_int *list)
{
    int *new_a = (int *)malloc(sizeof(int) * (list->capacity * 2));
    if (new_a == NULL)
    {
        fprintf(stderr, "ERROR: erro na alocação de memória");
        return -1; // Retorna -1 para indicar falha na alocação de memória.
    }

    for (int i = 0; i < list->capacity; i++)
    {
        new_a[i] = list->a[i];
    }

    free(list->a); // Libera a memória do array antigo.
    list->a = new_a;
    list->capacity = list->capacity * 2;

    return 0;
}

/*
    ====================================================================================
    Criação e inicialização de um vetor dinâmico

    1° - Alocar memória para uma nova estrutura do tipo array_list_int
    2° - Verificar se houve algum erro na alocação
    3° - Defino o ${size} como zero pois o vetor está vazio
    4° - Definir a capacidade do vetor
    5° - Alocar dinamicamente um array de inteiro dentro da estrutura
    6° - Verificar se a alocação de memória para ${a} deu certo
    7° - Retornar o ponteiro para a nova estrutura
    ====================================================================================
    Notação: O(1) Pois todoas as operações são O(1) e independe do tamanho dos dados e capacidade do vetor
*/
array_list_int *array_list_create()
{
    array_list_int *new_list = (array_list_int *)malloc(sizeof(array_list_int));
    if (new_list == 0)
    { /* Não foi possível alocar memória para a lista */
        fprintf(stderr, "Error on memory allocation.\n");
        exit(-1);
    }

    new_list->size = 0;
    new_list->capacity = 100;
    new_list->a = (int *)malloc(sizeof(int) * new_list->capacity); /* Tamanho inicial: 100*/
    if (new_list->a == 0)
    { /* Não foi possível alocar memória para a lista a */
        fprintf(stderr, "Error on memory allocation.\n");
        exit(-1);
    }

    return new_list; /* Retorna o ponteiro para a nova array_list alocada */
}

/*
    ====================================================================================
    Pegar elemento a partir do índice

    1° - Inicializa o erro como 0 (Sem erro)
    2° - Verifica se o índice é válido, menor que 0 || maior que o ${size} da lista
        2.1° - Defino o error como 1 e sai da função
    3° - Retorna o elemento na posição
    ====================================================================================
    Notação: O(1) Pois todas as operações são O(1) e independe do tamanho dos dados e capacidade do vetor

*/
int array_list_get(array_list_int *list, int index, int *error)
{
    *error = 0;
    if (index < 0 || index >= list->size)
    { /* O índice deve ser válido*/
        // fprintf(stderr, "Error: Indice fora do limites.\n");
        // exit(-1);
        *error = 1;
        return 0;
    }
    return list->a[index];
}

/*
    ====================================================================================
    Adicionar ao final do vetor

    1° - Verificar se ${capacity} == ${size}
        1.1° - Chamar increase memory para aumentar a capacidade, se a função retornar false
               retorna o tamanaho atual do vetor.
    2° - Inserimos o valor na posição ${list->size} de ${list->a}, pois queremos inserir ao final do
         vetor, logo o tamanho atual do vetor é o final do vetor.
    3° - Aumentamos o tamanho atual do vetor, Somando 1 ao ${size}
    4° - Retornamos o tamanho atual do vetor
    ====================================================================================
    Notação: O(N), pois avaliando o pior caso, entraríamos em increase memory, onde a notação é O(N)
             Mas nao entrando em increase memory, O(1)
*/
unsigned int array_list_push_back(array_list_int *list, int value)
{
    if (list->capacity == list->size)
    {
        if (increase_capacity(list)) /* Precisa aumentar a memória */
            return array_list_size(list);
    }
    list->a[list->size] = value;
    list->size++;
    return array_list_size(list);
}

/*
    ====================================================================================
    Remover ao final da lista
    1° - Verificar se a lista está vazia, true : Imprime erro
    2° - Se a lista nao está vazia, precisamos apenas subtrair 1 em ${size} para perder a referencia
         do último elemento
    3° - Retorna o novo tamanho do vetor
    ====================================================================================
    Notação: O(1), visto que independe do tamanho do vetor ou tamanho do elemento
 */
unsigned int array_list_pop_back(array_list_int *list)
{
    if (list->size == 0)
    {
        fprintf(stderr, "Error: Vetor está vazio. Não é possível remover elementos.\n");
        exit(-1);
    }

    list->size--;

    return array_list_size(list);
}

/*
    ====================================================================================
    Retorna o tamanho atual da lista
    1° - Retorna o ${size} da lista
    ====================================================================================
    Notação: O(1), visto que independe do tamanho do vetor ou tamanho do elemento
 */
unsigned int array_list_size(array_list_int *list)
{
    return list->size;
}

/*
    ====================================================================================
    Verifica se um elemento pertence ao array
    1° - Verificar se o vetor é válido
    2° - Iterar o vetor, verificando se o elemento procurado é igual a ${list->a[i]}
         2.1° - Se for igual retorna o índice
         2.2° - Se nao retorna -1
 */
int array_list_find(array_list_int *list, int element)
{
    if (list == NULL)
    {
        fprintf(stderr, "ERROR: Vetor inválido");
        exit(-1);
    }

    for (int i = 0; i < list->size; i++)
    {
        if (list->a[i] == element)
        {
            return i;
        }
    }

    return -1;
}

/*
    ====================================================================================
    Inserir em uma posição específica
    1° - Verificar se o índice é válido
    2° - Verificar se o vetor precisa de aumente de capacidade
         2.1° - Chamar increase memory para aumentar a capacidade, se a função retornar false
               retorna o erro.
    3° - Mover todos os elementos após o indice escolhe uma posição para a direita, abrindo espaço
    4° - Adicinar o elemento no indice
    5° - Adicionar 1 ao ${list->size}
    6° - Retornar O tamanho do vetor
    ====================================================================================
    Notação: O(N), pois depende do tamanho do vetor
 */
unsigned int array_list_insert_at(array_list_int *list, int index, int value)
{
    if (index > list->size || index < 0)
    {
        fprintf(stderr, "Error: Índice inválido.\n");
        exit(-1);
    }

    if (list->size == list->capacity)
    {
        if (!increase_capacity(list))
        {
            fprintf(stderr, "Error: Não foi possível aumentar a capacidade do vetor.\n");
            exit(-1);
        }
    }

    for (int i = list->size; i > index; i--)
    {
        list->a[i] = list->a[i - 1];
    }

    list->a[index] = value;
    list->size++;

    return array_list_size(list);
}

/*
    ====================================================================================
    Remover um elemento de um índice especifico

    1° - Verificar se o índice é válido
    2° - Iterar o vetor, a partir do ${index} recebe o valor do ${index + 1}
    3° - ${index--}
    4° - Retorna o tamanho atual do vetor
    ====================================================================================
    Notação: O(N), pois depende do tamanho do vetor
 */
unsigned int array_list_remove_from(array_list_int *list, int index)
{
    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Índice inválido");
        exit(-1);
    }

    for (int i = index; i < list->size; i++)
    {
        list->a[i] = list->a[i + 1];
    }

    list->size--;

    return array_list_size(list);
}

/*
    ====================================================================================
    Retorna a capacidade máxima do vetor

    ====================================================================================
    Notação: O(1), pois independe do tamanho do vetor
 */
unsigned int array_list_capacity(array_list_int *list)
{
    return list->capacity;
}

/*
    ====================================================================================
    Retorna a porcentagem de ocupação do vetor
    1° - Verificamos se o vetor é válido
    2° - retornamos a multiplicação de 100 com a divisão do ${list->size} por ${list->capacity},
         exemplo:
         ${list->size} = 39
         ${list->capacity} = 100
         porcento_ocupado = (39/100) * 100 = 39.0
    ====================================================================================
    Notação: O(1), pois independe do tamanho do vetor
 */
double array_list_percent_occupied(array_list_int *list)
{
    if (list->capacity == 0)
    {
        fprintf(stderr, "Error: Vetor inválido");
        exit(-1);
    }

    return ((double)list->size / (double)list->capacity) * 100;
}

/*
    ====================================================================================
    Apaga o nosso vetor, perdendo todas as referencias
    1° - Verificar se a lista é válida
    2° - liberar memória de ${list->a}
    3° - Libear memória de ${list}
    4° - zerar ${list->size} e ${list->capacity}
    ====================================================================================
    Notação: O(1), pois independe do tamanho do vetor
 */
void array_list_destroy(array_list_int *list)
{
    if (list->capacity == 0)
    {
        fprintf(stderr, "ERROR: Vetor inválido");
        exit(-1);
    }

    list->size = 0;
    list->capacity = 0;
    free(list->a);
    free(list);
}