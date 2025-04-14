#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
    int serversocket,port;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];

    serversocket=socket(AF_INET,SOCK_DGRAM,0);
    if(serversocket<0)
    {
        perror("Socket creation failed\n");
        exit(1);
    }

    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;

    printf("Enter the port no. : \n");
    scanf("%d",&port);

    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    if(bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        perror("binding failed\n");
        exit(1);
    }

    printf("Waiting for client to connect");

    bzero((char*)&clientaddr,sizeof(clientaddr));
    len=sizeof(clientaddr);
    bzero(message,sizeof(message));

    recvfrom(serversocket,message,sizeof(message),0,(struct sockaddr*)&clientaddr,&len);

    printf("\nConnection recieved from client\n");
    printf("client send message : %s \n",message);

    const char* reply="Your message is recieved";
    printf("\n sending message to client\n");

    sendto(serversocket,reply,sizeof("Your message is recieved"),0,(struct sockaddr*)&clientaddr,len);

    close(serversocket);
    return 0;
}