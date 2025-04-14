#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

// Function to check if number is prime
int isPrime(int n)
{
    if (n <= 1) return 0;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int serversocket, clientsocket, port, num;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    // 1. Create a socket
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0)
    {
        perror("\nSocket creation failed");
        exit(1);
    }

    // 2. Clear and set details
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("\nEnter the port no. : ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket to IP and port
    if (bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Binding failed.");
        exit(1);
    }

    // 4. Listen for connections
    listen(serversocket, 5);
    len = sizeof(clientaddr);

    printf("\nWaiting for client connection ...");

    // 5. Accept client connection
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    if (clientsocket < 0)
    {
        perror("\nAccept failed.");
        exit(1);
    }

    printf("\nClient connected");

    // 6. Ask client to send number
    write(clientsocket, "Enter a number: ", sizeof("Enter a number: "));

    // 7. Receive number from client
    read(clientsocket, &num, sizeof(num));
    printf("\nNumber received from client: %d\n", num);

    // 8. Send back result
    if (isPrime(num))
        write(clientsocket, "Number is prime", sizeof("Number is prime"));
    else
        write(clientsocket, "Number is not prime", sizeof("Number is not prime"));

    // 9. Close sockets
    close(serversocket);
    close(clientsocket);

    return 0;
}
