#ifndef CLIENT_H
#define CLIENT_H

#define MESSAGE_LENGTH 1000
char *ip_address;

int port;

int sockfd;

struct sockaddr_in ipv4_address;

void create_socket();

void *send_message(void *buffer);

void *receive_message(void *buffer);

#endif
