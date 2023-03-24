#include "linked-list.h"

#ifdef POINTER_IMPLEMENTATION
void printList(node *n)
{

    while (n != NULL) {
        printf("%d\n", n->ID);
        n = n->next;
    }
}

#else
void printList(node n)
{
    node *n1 = NULL;
    n1 = &n;
    while (n1 != NULL) {
        printf("%d\n", n1->ID);
        n1 = n1->next;
    }
    n1 = NULL;
}
#endif


int main (){

#ifdef POINTER_IMPLEMENTATION
// Implementation 1  
#pragma message ( "Using Implementation #1!" )  
    node *student1 = NULL;
    node *student2 = NULL;
    node *student3 = NULL;
    node *student4 = NULL;

    student1 = (node*)malloc(sizeof(node));
    student2 = (node*)malloc(sizeof(node));
    student3 = (node*)malloc(sizeof(node));
    student4 = (node*)malloc(sizeof(node));

    student1->ID = 0;
    student1->next = student2;
    student2->ID = 1;
    student2->next = student3;
    student3->ID = 2;
    student3->next = student4;
    student4->ID = 3;

#else
// Implementation 2
#pragma message ( "Using Implementation #2!" )  
    node student1, student2, student3, student4; 

    student1.ID = 0;
    student1.next = &student2;
    student2.ID = 1;
    student2.next = &student3;
    student3.ID = 2;
    student3.next = &student4;
    student4.ID = 3;
    student4.next = NULL;
#endif
    printList(student1);
 
    return 0;
}