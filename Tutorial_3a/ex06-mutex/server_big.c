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

#define MAX_CLIENTS 10

void *handle_client(void *arg) {
    int sockfd = *((int*)arg);
    char recv_message[1000];
    const char *hello = "Hello from server. Thanks for your message!";
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int n = recvfrom(sockfd, (char *)recv_message, 1000,
                MSG_WAITALL, (struct sockaddr *) &client_addr, &len);
    recv_message[n] = '\0';
    printf("Client: %s\n", recv_message);
    sendto(sockfd, (const char *)recv_message, strlen(recv_message),
            MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);

    printf("\nSent the received message back to client.\n");

    close(sockfd);
    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Missing arguments. Exiting!!!\n");
        return 2;
    } else if (argc > 2) {
        printf("Error: Too many arguments. Exiting!!!\n");
        return 2;
    }

    int port;
    sscanf(*(argv+1), "%d", &port);

    int sockfd;
    struct sockaddr_in server_addr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Filling server information
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *) &server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[MAX_CLIENTS];
    int num_active_clients = 0;

    while (1) {
        if (num_active_clients < MAX_CLIENTS) {
            int *sockfd_ptr = (int*)malloc(sizeof(int));
            *sockfd_ptr = accept(sockfd, (struct sockaddr *) &client_addr, &len);

            if (*sockfd_ptr < 0) {
                perror("accept failed");
                free(sockfd_ptr);
            } else {
                pthread_create(&threads[num_active_clients], NULL, handle_client, sockfd_ptr);
                num_active_clients++;
            }
        } else {
            printf("Server busy. Rejecting incoming request.\n");
            sleep(1);
        }
    }

    close(sockfd);
    return 0;
}