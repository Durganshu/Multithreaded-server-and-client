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

#include "server.h"

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Error: Missing arguments. Exiting!!!\n");
        return 2;
    }
    else if(argc > 2){
        printf("Error: Too many arguments. Exiting!!!\n");
        return 2;
    }
    
    sscanf(*(argv+1), "%d", &port);

	char recv_message[MESSAGE_LENGTH];
	
	create_socket();

	 if (listen(sockfd, N) == 0)
        printf("Listening\n");
    else
        printf("Error\n");

	pthread_t thread_a[NCLIENTS];
	int newSocket;
    struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	int i = 0;
 
    while (1) {
        addr_size = sizeof(serverStorage);
 
        // Extract the first
        // connection in the queue
        newSocket = accept(sockfd,
                           (struct sockaddr*)&serverStorage,
                           &addr_size);
        int choice = 0;
        recv(newSocket,
             &choice, sizeof(choice), 0);
 
		// Create thread
		if(pthread_create(&thread_a[i], NULL, handle_requests, recv_message)) {
        	fprintf(stderr, "Error creating thread\n");
        	return 1;
    	}
        // if (pthread_create(&readerthreads[i++], NULL,
        //                        reader, &newSocket)
        //     != 0)
 
        //     // Error in creating thread
        //     printf("Failed to create thread\n");
            
        
 
        if (i >= N) {
            // Update i
            i = 0;
 
            while (i < N) {
                // Suspend execution of
                // the calling thread
                // until the target
                // thread terminates
                pthread_join(thread_a[i],
                             NULL);
            }
 
            // Update i
            i = 0;
        }
    }
	// for(int i = 0; i <NCLIENTS; i++){
	// 	if(pthread_create(&thread_a[i], NULL, receive_message, recv_message)) {
    //     	fprintf(stderr, "Error creating thread\n");
    //     	return 1;
    // 	}
	// }

	// for (int i = 0; i < NCLIENTS; i++)
    //     pthread_join(thread_a[i], NULL);

	//handle_requests(recv_message);

}

void create_socket(){
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	
	// Filling server information
	server_addr.sin_family = AF_INET; // IPv4
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&server_addr,
			sizeof(server_addr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void *handle_requests(void *buffer){

	socklen_t len;
	//Receive message
	char *recv_buffer = buffer;
	len = sizeof(client_addr); 

	int n = recvfrom(sockfd, (char *)recv_buffer, MESSAGE_LENGTH,
				MSG_WAITALL, ( struct sockaddr *) &client_addr,
				&len);
	recv_buffer[n] = '\0';
	printf("\n(Thread# %ld) Received this message from the client :\n%s\n", (long)pthread_self(), recv_buffer);

	//Send reply
	sendto(sockfd, (const char *)recv_buffer, MESSAGE_LENGTH,
		MSG_CONFIRM, (const struct sockaddr *) &client_addr,
			len);
	
	printf("(Thread# %ld) Sent the received message back to client.\n", (long)pthread_self());

}
