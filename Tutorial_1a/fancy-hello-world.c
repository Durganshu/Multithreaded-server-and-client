#include <stdio.h>
#include <string.h>
#include "fancy-hello-world.h"

int main(void) {
    char output[100];
    strcpy(output, "Hello world, hello ");
    char name[20];
    printf("Enter the name: ");
    fgets(name, sizeof(name), stdin);
    hello_string(name, output); 
    printf("%s", output);
    return 0;
}

void hello_string(char* name, char* output) {
    strcat( output, name);
}