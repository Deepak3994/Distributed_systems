#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#define SA struct sockaddr
#define LISTENQ 5
int count(int fptr)
{   
    int count=0;
    char ch;
    while((ch=fgetc(fptr))!=EOF) {
            count++;
            printf("%c",ch);
        }
    return count;
}

int main(int argc,char**argv)
{
    int fd,sockfd,listenfd,connfd,filecount;
    pid_t childpid;
    char num;
    socklen_t client;
    struct sockaddr_in servaddr,cliaddr;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(atoi(argv[1]));
    bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);
    client=sizeof(cliaddr);
    connfd=accept(listenfd,(SA*)&cliaddr,&client);
    char buffer[100];
    FILE *fp;
    read(connfd,buffer,100);
    fp=fopen("add.txt","r");
    sscanf(buffer,"%d",&fp);
    filecount = count(fp);
    printf("the file count is %d",filecount);
 return 0;
}
     
     



   
