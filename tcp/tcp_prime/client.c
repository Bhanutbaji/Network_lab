#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>

int main()
{
    int clientsocket, port, number;
    struct sockaddr_in serveraddr;
    socklen_t len;
    char message[50];

    // 1. Create a socket
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Clear and set up server address details
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // loopback address (localhost)

    // 3. Connect to server
    printf("\nTrying to connect to the server...\n");
    if (connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server.\n");

    // 4. Receive prompt from server
    recv(clientsocket, message, sizeof(message), 0);
    printf("\nServer says: %s", message);

    // 5. Take number input from user and send to server
    scanf("%d", &number);
    send(clientsocket, &number, sizeof(number), 0);

    // 6. Receive and display result from server
    recv(clientsocket, message, sizeof(message), 0);
    printf("\nServer response: %s\n", message);

    // 7. Close socket
    close(clientsocket);

    return 0;
}
