#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int clientsocket,port;
    struct sockaddr_in serveraddr;
    char message[50];

    //1.create socket
    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    if(clientsocket<0)
    {
        perror("socket creation failed.\n");
        exit(1);
    }

    //2.clear and set
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;

    printf("\nEnter the port no : ");
    scanf("%d",&port);

    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    printf("Trying to connect to the server ...\n");

    //3.connect to server
    if(connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server\n");

    //4.send message to server
    printf("Sending message to the server..\n");
    send(clientsocket,"hello",strlen("hello")+1,0);

    //5.recieve message from server
    printf("Recieving message from the server..\n");
    recv(clientsocket,message,sizeof(message),0);
    printf("Message recieved from server : %s\n",message);

    //6.close socket
    close(clientsocket);
    return 0;
}