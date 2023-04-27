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

	//char recv_message[MESSAGE_LENGTH];
	
	create_socket();
	pthread_t threads[NCLIENTS];
	while(1){
		if (pthread_create(&threads[active_clients], NULL, handle_requests, NULL)) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
		pthread_detach(threads[active_clients]);
	}

    // while (1) {
    //     if (active_clients < N) {
    //         if (pthread_create(&threads[active_clients], NULL, handle_requests, NULL)) {
    //             fprintf(stderr, "Error creating thread\n");
    //             return 1;
    //         }
    //         pthread_detach(threads[active_clients]);
    //         active_clients++;
    //     }
    // }
	// handle_requests(recv_message);
	
	return 0;	

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

void *handle_requests(){

	socklen_t len;
	//Receive message
	char recv_buffer[MESSAGE_LENGTH];
	len = sizeof(client_addr); 
	
	
	while (1)
    {
		
        int n = recvfrom(sockfd, (char *)recv_buffer, 1000,
				MSG_WAITALL, ( struct sockaddr *) &client_addr,
				&len);
		
		recv_buffer[n] = '\0';

		printf("\n(Thread# %ld) Received this message from the client :\n%s\n", (long)pthread_self(), recv_buffer);

		pthread_mutex_lock(&mutex);
    	active_clients++;
    	pthread_mutex_unlock(&mutex);
    

		if (active_clients > NCLIENTS){
			printf("\n Too many requests. Incoming request discarded. \n");
		}
		else{
			sendto(sockfd, (const char *)recv_buffer, strlen(recv_buffer),
			MSG_CONFIRM, (const struct sockaddr *) &client_addr,
			len);
			printf("(Thread# %ld) Sent the received message back to client.\n", (long)pthread_self());
			
			pthread_mutex_lock(&mutex);
    		active_clients--;
    		pthread_mutex_unlock(&mutex);
		}
		

        fflush(stdout);
    }

}
