#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int ID;
    struct node* next;
} node;

#ifdef POINTER_IMPLEMENTATION
void printList(node *n);

#else
void printList(node n);
#endif

#endif //LINKED_LIST_H