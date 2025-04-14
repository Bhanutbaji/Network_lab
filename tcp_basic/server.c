#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
    int serversocket,clientsocket,port;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];

    //1.Create a socket
    serversocket=socket(AF_INET,SOCK_STREAM,0);
    if(serversocket<0)
    {
        perror("\nSocket creation failed");
        exit(1);
    }

    //2.Clear and set details
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;

    printf("\nEnter the port no. : ");
    scanf("%d",&port);

    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    //3.Bind socket to IP and port
    if(bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        perror("Binding failed.");
        exit(1);
    }

    //4.Listen for connections
    listen(serversocket,5);
    len=sizeof(clientaddr);

    printf("\nWaiting for client connection ...");

    //5.Accept client connection
    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    if(clientsocket<0)
    {
        perror("\nAccept failed.");
        exit(1);
    }

    printf("\nclient connected");
    printf("\nReading message from client...");

    //6.read message from client
    read(clientsocket,message,sizeof(message));
    printf("\nMessage recieved from client : %s\n",message);

    //7.respond to client
    printf("Sending message to client...\n");
    write(clientsocket,"message recieved",sizeof("message recieved"));

    //8.close socket
    close(serversocket);
    close(clientsocket);

    return 0;
}