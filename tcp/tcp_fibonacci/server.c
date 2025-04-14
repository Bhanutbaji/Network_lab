#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Function to generate Fibonacci sequence
void findFibonacci(int numrecieved, char fib[]);

int main()
{
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char fib[500] = "";  // To hold the Fibonacci series as a string
    int numrecieved;

    // 1. Create a TCP socket
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Set up server address structure
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind the socket to the specified IP and port
    if (bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // 4. Listen for incoming connections
    listen(serversocket, 5);
    len = sizeof(clientaddr);

    printf("\nWaiting for client connection...\n");

    // 5. Accept a client connection
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);
    if (clientsocket < 0) {
        perror("Accept failed");
        exit(1);
    }

    printf("\nClient connected successfully.\n");

    // 6. Request integer input from client
    write(clientsocket, "Enter an integer:", sizeof("Enter an integer:"));

    // 7. Read the integer from client
    read(clientsocket, &numrecieved, sizeof(numrecieved));
    printf("\nNumber received from client: %d\n", numrecieved);

    // 8. Generate Fibonacci series string
    findFibonacci(numrecieved, fib);

    // 9. Send the Fibonacci string back to the client
    write(clientsocket, fib, sizeof(fib));

    // 10. Close sockets
    close(clientsocket);
    close(serversocket);

    return 0;
}

// Function to generate Fibonacci series up to 'numrecieved' terms
void findFibonacci(int numrecieved, char fib[])
{
    int i;
    int first = 0, second = 1, next;

    for (i = 0; i < numrecieved; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }

        char str[10];
        sprintf(str, "%d", next);
        strcat(fib, str);
        strcat(fib, " ");
    }
}
