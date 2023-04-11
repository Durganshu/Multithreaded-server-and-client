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
    
    char message[1000];
    printf("Input your message (end the message with ;;):\n");
    scanf("%[^;;]s", message);
    //printf("\nReceived message:\n%s", message );
    char *ip_address = NULL;
    ip_address = *(argv+1);
    //printf("%s", ip_address);
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int port;
    sscanf(*(argv+2), "%d", &port);
    //printf("Extraxted port: %d\n", port);

    struct sockaddr_in ipv4_address;
    struct sockaddr* s;
    s = (struct sockaddr*)&ipv4_address;
    
    ipv4_address.sin_family = AF_INET;
    ipv4_address.sin_port = htons(port);
    ipv4_address.sin_addr.s_addr = inet_addr(ip_address);
    int sent_bytes = sendto(sockfd, message, strlen(message)+1, 0, (struct sockaddr*)&ipv4_address, sizeof(ipv4_address));

    printf("No. of bytes sent: %d\n", sent_bytes);

    return 0;
}