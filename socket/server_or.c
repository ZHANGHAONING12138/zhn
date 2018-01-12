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
#define BUFLEN 512  //LENGTH OF THE BUFFER
#define ORPORT 21028  //BACKEND-SERVER OR PORT UDP


int main(int argc , char *argv[])
{
//PARAMETERS OF COMMUNICATION
    struct sockaddr_in server,client;
    int socketinfo;
    int clen=sizeof(client);
    int sen,recv;
    int count=0;
    char buff[BUFLEN];
    char outcome[BUFLEN];
//SOCKET START.                               COPY ON WEBSITE
//CREATE
    socketinfo=socket(AF_INET,SOCK_DGRAM,0);
    if(socketinfo==-1)
    {
     printf("Could not create socket");
    }
    memset(&server,0,sizeof(server));//FILL WITH 0
    server.sin_family=AF_INET;
    server.sin_port=htons(ORPORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
//BIND
    if(bind(socketinfo,(struct sockaddr*)&server,sizeof(server))<0)
    {
     printf("Error binding, holy crap");
     return 1;
    }
//BOOT UP
    printf("The Server OR is up and running using UDP on port %d.\n",ORPORT);
    printf("The Server OR starts receiving lines from the edge server for OR computation. The computation results are:\n");
    while(1)
    {
     memset(&buff,0,BUFLEN);
//RECEIVE
     recv=recvfrom(socketinfo,buff,BUFLEN,0,(struct sockaddr *)&client,&clen);
     if(recv==-1)
     {
      printf("Error receive,holy crap");
      return 1;
     }     
     if(buff[0]=='e') //RECEIVE THE END MESSAGE, STOP RECEIVING, SHOW ON SCREEN
     {
       printf("The Server OR has successfully received %d lines from the edge server and finished all OR computations.\n",count);
       printf("The Server OR has successfully finished sending all computation results to the edge server.\n");
       count=0;	
       puts("\n");
     }
     else
     {
	      count++;
//EXTRACT THE TWO CALCULATING NUMBERS
	      char d[10]="0";
	      char e[10]="0";
	      int i=0,j=0,k=0,l=0;
	      while(buff[l]!='\0')
		{
		 if(buff[l]==',')
		 {
			l++;
			while(buff[l]!=',')
			{
				d[i]=buff[l];
				l++;
				i++;
			}
			l++;
			while((buff[l]>='0')&&(buff[l]<='9'))
			{
				e[k]=buff[l];
				l++;
				k++;	
			}
		 }
		 else
		 {
			 l++;
		 } 
		
	        }
	     int dlen=strlen(d);
	     int dlen1=10-dlen;
	     char f[]="0000000000";
	     f[10] = '\0';     
	     for(j=0;j<dlen1;j++)
		{
		 f[j]='0';
		}
	     for(i=0;j<10;j++)
		{
		 f[j]=d[i];
		 i++;
		}
	     char g[]="0000000000";
	     int dlen2=10-strlen(e);
	     g[10] = '\0';
	     for(j=0;j<dlen2;j++)
		{
		 g[j]='0';
		}
	     for(i=0;j<10;j++)
		{
		 g[j]=e[i];
		 i++;
		}
	     char h[]="0000000000";//STORE THE COMPUTATION RESULT(WITH PADDED 0 )
	     h[10]='\0';
	     for(j=0;j<10;j++)
		{
		 h[j]=f[j]|g[j];	
		}
             char new[11]="";//STORE THE COMPUTATION RESULT(WITHOUT PADDED 0)
	     int u=0,v=0;
	     int m=atoi(h);
	     if(m==0)
	     {
               strcpy(new,h);
             }
	     else
             {
	       while(h[u]!='\0')
	       {
	         while(h[u]=='0')
	 	 {u++;}
	  	 for(u;u<strlen(h);u++)
	  	 {   
	  	   new[v]=h[u];
	  	   v++;
	         }
	        }
	      }
	      printf("%s or %s=%s\n",d,e,new);//SHOW ON SCREEN
//REPLY
	      sen=sendto(socketinfo,new,11,0,(struct sockaddr*) &client,clen);
	      if (sen==-1)
	      {
	       printf("Error send,holy crap");
	      }
       }
//        puts("\n");
    }
//CLOSE
    close(socketinfo);
    return 0;
}
