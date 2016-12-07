#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int input[20],output[20];
sem_t mutex;
void* client(void *ptr) {
	int myid,port,op1,op2;
	char ipaddress[10];
   int sockfd, portno, n,operation;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[256];
   
   /*if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }*/
   sscanf((char*)(ptr),"%s%d%d%d%d%d",ipaddress,&port,&operation,&op1,&op2,&myid);
   sprintf(buffer,"%s\n%d\n%d\n%d\n%d\n%d",ipaddress,port,operation,op1,op2,myid);
   printf("%s%d%d%d%d%d",ipaddress,port,operation,op1,op2,myid);
   
   portno = port;
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   server = gethostbyname(ipaddress);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
   
   //printf("Please enter the message: ");
   //bzero(buffer,256);
   //fgets(buffer,255,stdin);
   //memset(buffer, '\n', sizeof(msg));
   //scanf("\n%s\n,%d\n,%s\n,%d\n,%d\n",buffer);
   //printf("\n%s\n,%d\n,%s\n,%d\n,%d\n", buffer);
   /* Send message to the server */
   n = write(sockfd,buffer, sizeof(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, &buffer[0], sizeof(buffer[0]));
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
   printf("\nvalue = %d\n",buffer[0]);
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
	if( sem_init(&mutex,1,1) < 0)
    {
      perror("semaphore initilization");
      exit(0);
    }
	printf("Input the number of threads to create\n");
    scanf("%d",&n);

    //printf("n=%d",n);
    /*for(i=0;i<n;i++)
    {
    printf("enter the input function number for thread i %d\n",i);
    scanf("%d",&input[i]);
	//printf("%d\n",input[i]);
	}*/

    //pthread_t thread
   
     //{
     	//sem_wait(&mutex);
	i=0;
     	a[i]=i;
     	//printf("enter ipaddress,port number, operation and operands\n");
     	//scanf("%s%d%d%d%d",ipaddress,&port,&operation,&op1,&op2);
	//ipaddress"172.16.51.255";
	port = 5005;
	operation = 0;
	op1 = 12;
	op2 = 3;
     	sprintf(buffer,"%s\n%d\n%d\n%d\n%d\n%d\n","172.16.51.46",port,operation,op1,op2,a[i++]);
	sprintf(buffer1,"%s\n%d\n%d\n%d\n%d\n%d\n","172.16.51.104",5006,operation,op1,op2,a[i++]);
	sprintf(buffer2,"%s\n%d\n%d\n%d\n%d\n%d\n","172.16.51.81",5007,operation,op1,op2,a[i]);
     	//sscanf(buffer,"%d\n",a[i]);
        //printf("\n%s\n,%d\n,%s\n,%d\n,%d\n%d\n", buffer);
     	ref = pthread_create( &thread[i--], NULL, client, (void*) buffer);
	ref = pthread_create( &thread[i--], NULL, client, (void*) buffer1);
	ref = pthread_create( &thread[i], NULL, client, (void*) buffer2);
     	//sem_post(&mutex);
     //}

     for (i = 0; i < n; i++)
     	pthread_join( thread[i], NULL);

     //for (i = 0; i < n; i++)
     	//printf("value=%d\n",output[i]);
    exit(0);
}

