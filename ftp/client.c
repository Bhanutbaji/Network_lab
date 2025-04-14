#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

#define SERV_TCP_PORT 5035
#define MAX 50

int main()
{
    int sockfd,n;
    struct sockaddr_in serveraddr;
    char filename[MAX],buff[MAX];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        perror("Socket creation failed\n");
        exit(1);
    }

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(SERV_TCP_PORT);

    if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        perror("Connection failed\n");
        close(sockfd);
        exit(1);
    }

    printf("enter the source file name");
    scanf("%s",filename);

    if(write(sockfd,filename,MAX)<0)
    {
        perror("Error sending filename");
        close(sockfd);
        exit(1);
    }

    printf("\n-----File content-----\n");
    while((n=read(sockfd,buff,MAX))>0)
    {
        buff[n]='\0';
        printf("%s",buff);
    }
    if(n<0)
    {
        perror("error reading from socket");
        exit(1);
    }
    close(sockfd);
    return 0; 
}