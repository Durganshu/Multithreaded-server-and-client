#ifndef SERVER_H
#define SERVER_H
#define MESSAGE_LENGTH 1000
#define NCLIENTS 2
#define N 2

int port, sockfd;

struct sockaddr_in server_addr, client_addr;

void create_socket();

void *handle_requests(void *buffer);

void *send_message(void *buffer);

void *receive_message(void *buffer);


#endif
