#include "double-linked-list.h"

int main (){

    node *head = NULL;
    node *student1 = NULL;
    node *student2 = NULL;
    node *student3 = NULL;
    node *student4 = NULL;

    student1 = (node*)malloc(sizeof(node));
    student2 = (node*)malloc(sizeof(node));
    student3 = (node*)malloc(sizeof(node));
    student4 = (node*)malloc(sizeof(node));

    student1->ID = 1;
    student1->prev = NULL;
    student1->next = student2;
    head = student1;

    student2->ID = 2;
    student2->prev = student1;
    student2->next = student3;
    
    student3->ID = 3;
    student3->prev = student2;
    student3->next = student4;

    student4->ID = 4;
    student4->prev = student3;
    student4->next = NULL;

    node *student5 = NULL;
    student5 = (node*)malloc(sizeof(node));
    student5->ID = 5;

    insert_node(&head, student3, student5);
    
    printList(head);
    remove_node(&head, student5);
    printf("After removing!:\n");
    printList(head);

    return 0;
}

void insert_node (node **head, node *prev, node *new_node){

    if(prev == NULL){   
        (*head)->prev = new_node;
        new_node->prev = NULL;
        new_node->next = *head;
        *head = new_node;
    }
    else if(prev->next != NULL){
        node *temp = prev->next;
        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = temp;
    }  
    else{
        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = NULL;
    }
}

void remove_node (node **head, node *n){
    if(n==*head){
        
    }
    else{
        (n->prev)->next = n->next;
        (n->next)->prev = (n->prev);
    }   
}

void printList(node *n)
{

    while (n != NULL) {
        printf("%d\n", n->ID);
        n = n->next;
    }
}