#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "client.h"

int main(int argc, char *argv[]){

    if (argc < 3){
        printf("Error: Missing arguments. Exiting!!!\n");
        return 2;
    }
    else if(argc > 3){
        printf("Error: Too many arguments. Exiting!!!\n");
        return 2;
    }
    

    char sent_message[MESSAGE_LENGTH];
    // char sent_message[MESSAGE_LENGTH] = "Hello! I'm one of the clients who's trying to ping you!";
    char recv_buffer[MESSAGE_LENGTH]; 
    printf("(Taking user input through the primary thread)\n");
    printf("Input your message (end the message with ;):\n");
    scanf("%[^;]s", sent_message);
    ip_address = *(argv+1);
    sscanf(*(argv+2), "%d", &port);

    create_socket();
    pthread_t thread_a[2];

    if(pthread_create(&thread_a[0], NULL, send_message, sent_message)) {
        	fprintf(stderr, "Error creating thread\n");
        	return 1;
    }

    if(pthread_create(&thread_a[1], NULL, receive_message, recv_buffer)) {
        	fprintf(stderr, "Error creating thread\n");
        	return 1;
    }


    for (int i = 0; i < 2; i++)
        pthread_join(thread_a[i], NULL);

    close(sockfd);

    return 0;
}

void create_socket(){

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&ipv4_address, 0, sizeof(ipv4_address));
	
    
    ipv4_address.sin_family = AF_INET;
    ipv4_address.sin_port = htons(port);
    ipv4_address.sin_addr.s_addr = inet_addr(ip_address);
    //ipv4_address.sin_addr.s_addr = INADDR_ANY;
}

void *send_message(void *buffer){
    
    char *send_buffer = buffer;
    int sent_bytes = sendto(sockfd, (const char *)send_buffer, 
        strlen(send_buffer)+1, MSG_CONFIRM, 
        (struct sockaddr*)&ipv4_address, sizeof(ipv4_address));

    printf("(Thread# %ld) %d bytes sent to server.\n", (long)pthread_self(), sent_bytes);

    return NULL;
}

void *receive_message(void *buffer){

    char *recv_buffer = buffer;
    socklen_t length;
    int n = recvfrom(sockfd, (char *)recv_buffer, MESSAGE_LENGTH, 
                MSG_WAITALL, (struct sockaddr *) &ipv4_address,
                &length);
    recv_buffer[n] = '\0';
    printf("\n(Thread# %ld) Received this reply from the server :\n%s\n", (long)pthread_self(), recv_buffer);

    return NULL;
}