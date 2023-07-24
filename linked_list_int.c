#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma lista, ela é composta pelo seu tamanho, um ponteiro
// para o primeiro elemento da lista e outro para o último elemento da lista.
struct list
{
    unsigned int size;
    struct node *first;
    struct node *last;
};

// Estutura de cada nó da nossa lista
// Composto pelo seu dado, um ponteiro para o proximo nó, e outro para o nó anterior
struct node
{
    int data;
    struct node *next;
    struct node *previous;
};

/*
    ====================================================================================
    Função para criar um novo nó

    1° - Criar um ponteiro do tipo node alocando memória
    2° - Verificar se o passo anterior foi bem sucedido
    3° - Atribuir o value ao ${new_node->data}
    4° - Definir ${new_node->next} e ${new_node->previous} como nulo
    5° - Retornar nosso new_node
    ====================================================================================
    NOTAÇÃO: O(1), pois independe do tamanho do valor
*/
struct node *create_node(int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        fprintf(stderr, "ERROR: erro na alocação de memória");
        exit(-1);
    }

    new_node->data = value;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}

/*
    ====================================================================================
    Função para criar a lista duplamente ligada

    1° - Aloca memória dinamicamente para um ponteiro de uma nova lista
    2° - Verifica se o passo anterior foi bem sucedido
    3° - Define o first e o last como nulos
    4° - Defino o size como 0
    5° - Retorna a nova lista
    ====================================================================================
    Notação: O(1)
*/
struct list *linked_list_create()
{
    struct list *new_list = (struct list *)malloc(sizeof(struct list));
    if (new_list == NULL)
    {
        fprintf(stderr, "ERROR: Erro de alocação de memória");
        exit(-1);
    }

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->size = 0;
    return new_list;
}

/*
    ====================================================================================
    Função para adicionar ao fim da lista

    1° - Criamos um novo nó
    2° - Vericamos se a lista é vazia
    3° - Se a lista esta vazia:
        3.1° - Setamos o fim e o inicio da lista como nosso novo nó
    4° - Se não é vazia:
        4.1° - O proximo em relação ao antigo fim da lista é o nosso novo nó
        4.2° - O anterior em relação ao nosso novo nó é o antigo fim da lista
        4.3° - E por fim, atualizamos o nosso fim da lista, como nosso novo nó
    5° - Independe da lista ser vazia ou nao, adicionamos 1 ao tamanho da lista
    ====================================================================================
    Notação: O(1)
*/
void linked_list_push_back(struct list *list, int value)
{
    struct node *new_node = create_node(value);
    if (list->first == NULL)
    {
        list->first = new_node;
        list->last = new_node;
    }
    else
    {
        list->last->next = new_node;
        new_node->previous = list->last;
        list->last = new_node;
    }
    list->size++;
}

/*
    ====================================================================================
    Função para adicionar ao início da lista

    1° - Criamos um novo nó
    2° - Verificamos se a lista está vazia
    3° - Se estiver vazia:
        3.1 - Definimos o novo nó como primeiro e ultimo da lista
    4° - Se não:
        4.1° - O anterior em relação ao antigo primeiro é o novo no
        4.2° - O proximo, em relação ao novo no, é o antigo primeiro
        4.3° - Atualizamos o primeiro no da lista para ser o novo nó
    5° - Independente de estar vazia ou nao, somamos 1 ao tamanho da lista
    ====================================================================================
    Notação: O(1)
*/
void linked_list_push_front(struct list *list, int value)
{
    struct node *new_node = create_node(value);
    if (list->first == NULL)
    {
        list->first = new_node;
        list->last = new_node;
    }
    else
    {
        list->first->previous = new_node;
        new_node->next = list->first;
        list->first = new_node;
    }
    list->size++;
}

/*
    ====================================================================================
    Adiconar um no em uma posição específica da lista

    1° - Verificar se o index está dentos dos intervalos
    2° - Criar uma novo nó com o valor
    3° - Verificar se o índice é 0, se for, chamamos a funçao de
         Inserior no incio.
    4° - Verificar se o index == size da lista, se for, inserimos
         ao final da lista
    5° - Se nao for nem no inico e nem fim, é no meio da lista, logo:
        5.1° - Criamos uma no atual como referencia
        5.2° - Iteramos até chegar na posição de index
        5.3° - Definimos o anterior do novo nó como o nó de referencia
        5.4° - Definimos o prox do novo nó com o prox do nó de referencia
        5.5° - Definimos o anterior do proximo do nó de referencia como o novo nó
        5.6° - Definimos o prox do nó de referencia como o novo nó
    6° - Adicionamos 1 ao tamanho da lista
    ====================================================================================
    Notação: O(N), pois no pior caso, o índice seria ${tamanho da lista - 1}
             E o while percorreria a lista quase toda, logo cresce lineramente
             ao valor do indice
*/
void linked_list_push_at(struct list *list, int value, int index)
{
    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Índice invalido");
        exit(-1);
    }

    struct node *new_node = create_node(value);

    if (index == 0)
    {
        linked_list_push_front(list, value);
    }
    else if (index == list->size)
    {
        linked_list_push_back(list, value);
    }
    else
    {
        struct node *cur_node = list->first;
        int i = 0;
        while (i < index)
        {
            cur_node = cur_node->next;
            i++;
        }
        new_node->previous = cur_node;
        new_node->next = cur_node->next;
        cur_node->next->previous = new_node;
        cur_node->next = new_node;
    }
    list->size++;
}

/*
    ====================================================================================
    Função para remover o ultimo elemento da lista

    1° - Verificar se a lista está vazia
    2° - Verificar se a lista tem apenas um elemento
        2.1° - Se a lista tem apenas um elemento, Após a remoção
               nao tera nem primeiro elemento, nem ultimo
    3° - Caso existam mais de elementos na lista
        3.1° - Criamos um no para guardar o antigo ultimo
        3.2° - Atualizamos o ultimo da lista para o anterior do antigo ultimo
        3.3° - Definimos o proximo do ultimo atual como nulo, afinal ele é o ultimo
        3.4° - Liberamos a memória do antigo ultimo da lista
    4° - Por fim, diminuimos 1 no tamanho da lista
    ====================================================================================
    Notação: O(1)
*/
void linked_list_remove_back(struct list *list)
{
    if (list->first == NULL)
    {
        fprintf(stderr, "ERROR: A lista está vazia");
        exit(-1);
    }

    if (list->first == list->last)
    {
        free(list->first);
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        struct node *last_node = list->last;
        list->last = last_node->previous;
        list->last->next = NULL;
        free(last_node);
    }
    list->size--;
}

/*
    ====================================================================================
    Função para remover o primeiro elemento da lista

    1° - Verifica se a lista está vazia
    2° - Verifica se a lista possui apenas um elemento
        2.1° - Se sim, define o primeiro e ultimo elemento como nulo
    3° - Se nao
        3.1° - Criamos um no para guardar o antigo primeiro
        3.2° - Atualizamos o primeiro no para o proximo apos o antigo primeiro
        3.3° - Definimos o anterior ao nosso atual primeiro no como nulo, pois
               Não existe ninguem antes dele, afinal ele é o primeiro
        3.4° - Liberamos a memória do nosso antigo primeiro no
    4° - Subtraimos 1 ao tamanho da lista, afinal, um elemento foi removido
    ====================================================================================
    Notaçao: O(1)
*/
void linked_list_remove_front(struct list *list)
{
    if (list->first == NULL)
    {
        fprintf(stderr, "ERROR: A lista está vazia");
        exit(-1);
    }

    if (list->last == list->first)
    {
        free(list->first);
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        struct node *first_node = list->first;
        list->first = first_node->next;
        list->first->previous = NULL;
        free(first_node);
    }

    list->size--;
}

/*
    ====================================================================================
    Remover de um local especifico

    1° - Verifica se a lista é vazia
    2° - Verifica se é o primeiro nó
    3° - Verifica se é o ultimo nó
    4° - Itera a nossa lista até chegar no indice requerido
        4.1° - Define o anterior do nosso proximo como o nosso anterior
        4.2° - Defino o proximo do nosso anterior, como o nosso proximo
        4.3° - Libera memória e subtrai um ao tamanha da lista
    ====================================================================================
    Notação O(N), pois depende do tamanho da lista e valor de indice pedido
*/

void linked_list_remove_from(struct list *list, int index)
{
    if (list == NULL || list->first == NULL)
    {
        fprintf(stderr, "ERROR: A lista está vazia");
        exit(-1);
    }

    if (index == 0)
    {
        linked_list_remove_front(list);
    }
    else if (index == list->size - 1)
    {
        linked_list_remove_back(list);
    }
    else
    {
        struct node *current = list->first;
        int i = 0;
        while (i < index)
        {
            current = current->next;
            i++;
        }

        current->previous->next = current->next;
        current->next->previous = current->previous;
        free(current);
        list->size--;
    }
}

// Função para ter o tamanho da lista
// Ela é do tipo size_t, size_t é utilizado para representar tamanhos
// e índices nao negativos.
// Recebe uma lista como parametro e retorna o seu size
size_t list_size(struct list *list)
{
    return list->size;
}

/*
    ====================================================================================
    Função para destruir a lista

    1° Verificar se a lista é vazia
    2° Criar um nó como referencia
    3° Iterar a nossa lista
        3.1° - Criamos um nó para ser o proximo do atual
        3.2° - Liberamos a memória do atual
        3.3° - Definimos o atual como o nosso proximo
        3.4 - VOLTA PARA O 3.1
    4° - Por fim liberamos o memória da lista
    ====================================================================================
    Notação: O(N), pois depende do tamanho da lista
*/

void destroy_list(struct list *list)
{
    if (list->first == NULL)
        return;

    struct node *current = list->first;
    while (current != NULL)
    {
        struct node *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

/*
    ====================================================================================
    Função para imprimir a lista

    1° - Verificamos se a lista nunca foi inicializada ou se ela está vazia
    2° - Criamos um current, definimos como o primeiro, e iteramos
         a lista printando o current, e definindo o currento como
         o current->next
    ====================================================================================
    Notação: O(N), pois depende do tamanho da lista
*/
void print_list(struct list *list)
{
    if (list == NULL || list->first == NULL)
    {
        fprintf(stderr, "ERROR: A lista está vazia");
    }

    struct node *current = list->first;
    printf("Lista: [");
    while (current != NULL)
    {
        printf("%d ,", current->data);
        current = current->next;
    }
    printf("]\n");
}