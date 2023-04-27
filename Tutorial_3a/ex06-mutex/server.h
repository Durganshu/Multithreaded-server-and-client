#ifndef SERVER_H
#define SERVER_H
#define MESSAGE_LENGTH 1000
#define NCLIENTS 2
#define N 2

int port, sockfd;

int active_clients = 0;

struct sockaddr_in server_addr, client_addr;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void create_socket();

//void *handle_requests(void *buffer);
void *handle_requests();

void *send_message(void *buffer);

void *receive_message(void *buffer);


#endif
