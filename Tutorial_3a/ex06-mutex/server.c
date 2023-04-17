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

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Error: Missing arguments. Exiting!!!\n");
        return 2;
    }
    else if(argc > 2){
        printf("Error: Too many arguments. Exiting!!!\n");
        return 2;
    }
    
    int port;
    sscanf(*(argv+1), "%d", &port);

    int sockfd;
	char recv_message[1000];
	const char *hello = "Hello from server. Thanks for your message!";
	struct sockaddr_in server_addr, client_addr;
	
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
	
	socklen_t len;

	len = sizeof(client_addr); //len is value/result

	int n = recvfrom(sockfd, (char *)recv_message, 1000,
				MSG_WAITALL, ( struct sockaddr *) &client_addr,
				&len);
	recv_message[n] = '\0';
	printf("Client : %s\n", recv_message);
    sendto(sockfd, (const char *)recv_message, strlen(recv_message),
		MSG_CONFIRM, (const struct sockaddr *) &client_addr,
			len);
	
	printf("\n Sent the received message back to client.\n");
}