#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int num_clients = 0;  // number of currently active clients
pthread_mutex_t lock; // mutex for accessing num_clients

void *client_handler(void *arg) {
    int sockfd = *(int *)arg;
    char buffer[BUFFER_SIZE];
    ssize_t n;

    pthread_mutex_lock(&lock);
    if (num_clients >= MAX_CLIENTS) {
        // too many active clients, close the socket
        close(sockfd);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    // increase the number of active clients
    num_clients++;
    pthread_mutex_unlock(&lock);

    // receive messages from the client and echo them back
    while ((n = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
        send(sockfd, buffer, n, 0);
    }

    // decrease the number of active clients
    pthread_mutex_lock(&lock);
    num_clients--;
    pthread_mutex_unlock(&lock);

    close(sockfd);
    return NULL;
}

int main(int argc, char **argv) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    pthread_t threads[MAX_CLIENTS];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    while (1) {
        clilen = sizeof(cli_addr);
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        // spawn a new thread to handle the client
        pthread_create(&threads[num_clients], NULL, client_handler, &newsockfd);
    }

    return 0;
}

