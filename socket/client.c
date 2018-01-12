#include<stdio.h>
#include<sys/socket.h> 
#include<sys/types.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include<stdlib.h>
#define BUFF 512  //LENGTH OF BUFFER
#define TCPPORT 23028 //EDGESERVER TCP PORT
int main(int argc , char *argv[])
{
//PARAMETERS OF COMMUNICATION
    int socketfd=0;
    struct sockaddr_in server;    
    char message[BUFF]="ganjinshou";//END MESSAGE:LET EDGE STOP RECEIVING
//OPEN THE FILE AND SAVE   
    FILE *pointer;
    char filebuff[255]; 
    char orifile[100][200]={0};
   // char ofile[200]={"0"};
    pointer=fopen(argv[1],"r");
    int i=0,j=0,count=0;
    while(fgets(filebuff,255,pointer)!=NULL)//STORE THE CONTENS OF FILE 
    {	
	if(filebuff[0]=='o'||filebuff[0]=='a')
	count++;
	for(i=0;i<strlen(filebuff);i++)
	{
               	orifile[j][i]=filebuff[i];//STORE THE CONTENTS LINE BY LINE
	}
	j++;
    }
//SOCKET START.                                 COPY ON WEBSITE
//CREATE
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(socketfd==-1)
    {
     printf("Could not create socket");
     return 1;
    }    
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_family=AF_INET;
    server.sin_port=htons(TCPPORT);    
//CONNECT
    if(connect(socketfd,(struct sockaddr *)&server,sizeof(server))<0)
    {
     printf("Error connection holy crap");
     return 1;
    } 
   puts("The client is up and running.");
//SEND
      for(i=0;i<count;i++)
      {	
	send(socketfd,orifile[i],strlen(orifile[i]),0);
      }		
      printf("The client has successfully finished sending %d lines to the edge server.\n",count);
	send(socketfd,message,strlen(message),0);
//READ
       char outbuff[BUFF][BUFF]={'\0'}; //STORE THE COMPUTATION RESULTS
	for(i=0;i<count;i++)
	{
		if(recv(socketfd,outbuff[i],BUFF,0)<0)
      		{
      		 printf("Read failed.Holy crap");
		 return 1;
     		}    	
	}
	puts("The client has successfully finished receiving all computation results from the edge server.");
	puts("The final computation result are:\n");
	for(j=0;j<count;j++)
	{
		printf("%s",outbuff[j]);
	}
	puts("\n");
//CLOSE
    close(socketfd);
    return 0;
}
