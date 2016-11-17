#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include"errno.h"
#include"rpc/rpc.h"
#include"square.h"

int input[20],output[20];
sem_t mutex;
void* client(void *ptr) {
  CLIENT *cl;
 square_in in;
 square_out *outp;
	int myid,port,op1,op2;
	char ipaddress[10];
   int sockfd, portno, n,operation;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
  char buffer[256];
  //printf("%s",(char*)ptr);
  sscanf((char*)ptr,"%s%d%d%d%d",ipaddress,&operation,&op1,&op2,&myid);
  printf("%s",ipaddress);
  cl=clnt_create(ipaddress,SQUARE_PROG,SQUARE_VERS,"tcp");
  in.arg1=atol("16");

     if(cl==NULL)
     {
           printf("\nerror:%s",strerror(errno));
           exit(-1);
     }

     if((outp=squareproc_1(&in,cl))==NULL)
     {
           //printf("\nerror :%s",clnt_sperror(cl,argv[1]));
           exit(-1);
     }

     printf("\n\n result is : %ld",outp->res1);
    
   
  return 0;
}


int main()
{
	int n,ref,i;
	int a[20];
	int *tid;
	char buffer[256], buffer1[256],buffer2[256];
	pthread_t thread[20];
	int myid,port,op1,op2,operation;
	char ipaddress[10];
	printf("Input the number of threads to create\n");
  scanf("%d",&n);

  i=0;
  a[1]= 1;
  a[2] = 2;
  
	port = 5005;
	operation = 0;
	op1 = 12;
	op2 = 3;
  sprintf(buffer,"%s\n%d\n%d\n%d\n%d\n","127.0.0.1",operation,op1,op2,a[i++]);
	//sprintf(buffer1,"%s\n%d\n%d\n%d\n%d\n","172.16.50.113",operation,op1,op2,a[i++]);
	ref = pthread_create( &thread[--i], NULL, client, (void*) buffer);
	//ref = pthread_create( &thread[--i], NULL, client, (void*) buffer1);
	
  //   for (i = 0; i < 1; i++)
     	pthread_join(thread[i], NULL);

      exit(0);
}

