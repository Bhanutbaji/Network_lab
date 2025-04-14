// client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    char message[100], input[100];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);
    getchar();  // consume newline

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Trying to connect to the server...\n");
    if (connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to the server.\n");

    recv(clientsocket, message, sizeof(message), 0);
    printf("%s", message);

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // remove newline

    send(clientsocket, input, strlen(input) + 1, 0);

    recv(clientsocket, message, sizeof(message), 0);
    printf("Reversed string from server: %s\n", message);

    close(clientsocket);
    return 0;
}
