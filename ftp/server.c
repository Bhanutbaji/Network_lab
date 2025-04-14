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
#define MAX 60

int main(int argc,char* argv[])
{
    int sockfd,newsockfd,clength;
    struct sockaddr_in serveraddr,clientaddr;
    char filename[MAX],buff[4096];
    FILE *f1;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=htons(SERV_TCP_PORT);

    bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("Binded\n");

    listen(sockfd,5);
    printf("Listening for connections\n");

    clength=sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&clength);
    printf("\n accepted");

    close(sockfd);

    read(newsockfd,filename,MAX);
    printf("\nCLient message :\nFile name: %s\n",filename);

    f1=fopen(filename,"r");
    if(f1==NULL)
    {
        perror("Error opening the file");
        exit(1);
    }
    while(fgets(buff,sizeof(buff),f1)!=NULL)
    {
        write(newsockfd,buff,strlen(buff));
    }
    fclose(f1);
    printf("File transferred");
    close(newsockfd);
    return 0;
}
