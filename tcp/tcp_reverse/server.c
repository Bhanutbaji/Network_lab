#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<netinet/in.h>  // Needed for sockaddr_in

int reverse(int n);

int main()
{
    int serversocket, clientsocket, port; 
    struct sockaddr_in serveraddr, clientaddr; 
    socklen_t len;  
    int numrecieved, reversenum;

    serversocket = socket(AF_INET, SOCK_STREAM, 0); 
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port); 
    serveraddr.sin_addr.s_addr = INADDR_ANY; 

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); 
    listen(serversocket, 5); 

    printf("\nWaiting for client connection...\n"); 
    len = sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);

    printf("\nClient connected.\n");

    write(clientsocket, "Enter an integer:", sizeof("Enter an integer:")); 
    read(clientsocket, &numrecieved, sizeof(numrecieved));
    printf("\nNumber received from client: %d\n", numrecieved);

    reversenum = reverse(numrecieved);
    write(clientsocket, &reversenum, sizeof(reversenum));

    close(clientsocket);
    close(serversocket);
    return 0;
}

int reverse(int n)
{
    int rev = 0;
    while(n != 0)
    {
        rev = rev * 10 + n % 10;
        n = n / 10;
    }
    return rev;
}
