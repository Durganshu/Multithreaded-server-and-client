#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int ID;
    struct node* prev;
    struct node* next;
} node;

void insert_node (node **head, node *prev, node *new_node);
void remove_node (node **head, node *n);
void printList(node *n);

#endif //DOUBLE_LINKED_LIST_H