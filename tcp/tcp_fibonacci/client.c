#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // for inet_addr

int main()
{
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    char message[500];  // buffer to store messages from server
    int number;

    // 1. Create socket
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Clear serveraddr and set parameters
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);

    // Set server IP address to localhost (127.0.0.1)
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect to server
    printf("\nTrying to connect to the server...\n");
    if (connect(clientsocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("\nConnected to the server.\n");

    // 4. Receive message from server
    recv(clientsocket, message, sizeof(message), 0);
    printf("\n%s ", message);

    // 5. Get number input and send to server
    scanf("%d", &number);
    send(clientsocket, &number, sizeof(number), 0);

    // 6. Receive Fibonacci result
    bzero(message, sizeof(message));
    recv(clientsocket, message, sizeof(message), 0);
    printf("\nFibonacci Series from Server: %s\n", message);

    // 7. Close socket
    close(clientsocket);
    return 0;
}
