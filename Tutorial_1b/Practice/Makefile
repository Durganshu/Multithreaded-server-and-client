IMPLEMENTATION=POINTER_IMPLEMENTATION
#IMPLEMENTATION=NOT_POINTER_IMPLEMENTATION
all: linked-list double-linked-list 
linked-list: linked-list.o
	cc -g -o linked-list linked-list.o
 
linked-list.o: linked-list.c
	cc -c -Wall -g linked-list.c -D$(IMPLEMENTATION)

double-linked-list: double-linked-list.o
	cc -g -o double-linked-list double-linked-list.o
 
double-linked-list.o: double-linked-list.c
	cc -c -Wall -g double-linked-list.c 

clean:
	rm linked-list.o linked-list double-linked-list.o double-linked-list 