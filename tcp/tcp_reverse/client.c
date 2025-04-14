#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_addr

int main() {
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    char message[50];
    int number, result;

    // 1. Create socket
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Clear and set server address
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    // 3. Ask for port and set up server address
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // 4. Connect to server
    printf("\nTrying to connect to the server...\n");
    if (connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to the server.\n");

    // 5. Receive message from server
    recv(clientsocket, message, sizeof(message), 0);
    printf("%s ", message);

    // 6. Read number from user and send to server
    scanf("%d", &number);
    send(clientsocket, &number, sizeof(number), 0);

    // 7. Receive result from server
    recv(clientsocket, &result, sizeof(result), 0);
    printf("Result is %d\n", result);

    // 8. Close socket
    close(clientsocket);
    return 0;
}
