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
#include <semaphore.h>

#include "server.h"

#define MAX_CLIENTS 10

sem_t active_clients;
pthread_mutex_t active_mutex = PTHREAD_MUTEX_INITIALIZER;
int active_count = 0;

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
    create_socket();
    sem_init(&active_clients, 0, MAX_CLIENTS);
    pthread_t threads[MAX_CLIENTS];
    for(int i=0;i<MAX_CLIENTS;i++){
        pthread_create(&threads[i], NULL, handle_requests, (void *)(long)i);
    }
    for(int i=0;i<MAX_CLIENTS;i++){
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&active_clients);
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

void *handle_requests(void *arg){
    int tid = (long)arg;
    socklen_t len;
    //Receive message
    char recv_buffer[MESSAGE_LENGTH];
    len = sizeof(client_addr);
    while (1)
    {   
        sem_wait(&active_clients);
        pthread_mutex_lock(&active_mutex);
        active_count++;
        pthread_mutex_unlock(&active_mutex);
        if (active_count > MAX_CLIENTS){
            printf("\n(Thread# %d) Maximum number of concurrent clients reached. \
                Will proceed when the threads are avialble... :\n", tid);
        }
        
    
        int n = recvfrom(sockfd, (char *)recv_buffer, 1000,
                MSG_WAITALL, ( struct sockaddr *) &client_addr,
                &len);
        recv_buffer[n] = '\0';
        
        printf("\n(Thread# %d) Received this message from the client :\n%s\n", 
        tid, recv_buffer);
        
        //usleep(5000000);

        sendto(sockfd, (const char *)recv_buffer, strlen(recv_buffer),
            MSG_CONFIRM, (const struct sockaddr *) &client_addr,
            len);
        
        printf("\n(Thread# %d) Sent the received message back to client.\n", tid);
        
        fflush(stdout);

        pthread_mutex_lock(&active_mutex);
        active_count--;
        pthread_mutex_unlock(&active_mutex);
        sem_post(&active_clients);
    }
    return NULL;
}
