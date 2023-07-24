#ifndef LINKED_LIST_INT_H
#define LINKED_LIST_INT_H

#include <stddef.h> // Incluir esta linha para definir "size_t"

// Estrutura de uma lista duplamente ligada
struct list;

// Função para criar um novo nó
struct node *create_node(int value);

// Função para criar a lista duplamente ligada
struct list *linked_list_create();

// Função para adicionar ao fim da lista
void linked_list_push_back(struct list *list, int value);

// Função para adicionar ao início da lista
void linked_list_push_front(struct list *list, int value);

// Função para adicionar um nó em uma posição específica da lista
void linked_list_push_at(struct list *list, int value, int index);

// Função para remover o último elemento da lista
void linked_list_remove_back(struct list *list);

// Função para remover o primeiro elemento da lista
void linked_list_remove_front(struct list *list);

// Função para remover de um local específico da lista
void linked_list_remove_from(struct list *list, int index);

// Função para obter o tamanho da lista
size_t list_size(struct list *list);

// Função para destruir a lista
void destroy_list(struct list *list);

// Função para imprimir a lista
void print_list(struct list *list);

#endif // LINKED_LIST_INT_H
