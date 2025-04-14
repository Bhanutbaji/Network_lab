#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
    int clientsocket,port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    struct hostent *server;
    char message[50];

    clientsocket=socket(AF_INET,SOCK_DGRAM,0);
    if(clientsocket<0)
    {
        perror("Socket creation failed\n");
        exit(1);
    }

    bzero((char*)&serveraddr,sizeof(serveraddr));
    printf("Enter the port no :\n");
    scanf("%d",&port);
    getchar();
    
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    len=sizeof(serveraddr);

    printf("Enter message to send to server: ");
    fgets(message, sizeof(message), stdin);

    printf("\nsending message to server\n");
    sendto(clientsocket,message,strlen(message)+1,0,(struct sockaddr*)&serveraddr,len);

    bzero(message,sizeof(message));
    printf("recieving message from server\n");
    recvfrom(clientsocket,message,sizeof(message),0,(struct sockaddr*)&serveraddr,&len);

    printf("\nmessage recieved from server :%s\n",message);
    close(clientsocket);
    return 0;
}