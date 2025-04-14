// server.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

void reverseString(const char *input, char *reversed);

int main() {
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char recv_str[100], reversed[100];

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 5);
    printf("Waiting for client connection...\n");

    len = sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    printf("Client connected.\n");

    write(clientsocket, "Enter a string: ", strlen("Enter a string: ") + 1);

    read(clientsocket, recv_str, sizeof(recv_str));
    printf("String received from client: %s\n", recv_str);

    reverseString(recv_str, reversed);

    write(clientsocket, reversed, strlen(reversed) + 1);

    close(clientsocket);
    close(serversocket);

    return 0;
}

void reverseString(const char *input, char *reversed) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        reversed[i] = input[len - i - 1];
    }
    reversed[len] = '\0';
}
