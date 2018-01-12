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
#define ORPORT 21028   //BACKEND-SERVER OR PORT UDP
#define ANDPORT 22028  //BACKEND-SERVER AND PORT UDP
#define TCPPORT 23028 //EDGESERVER TCP PORT
#define UDPPORT 24028 //EDGESERVER UDP PORT
#define BUFLEN 3000     //LENGTH OF BUFFER
//PARAMETERS OF UDP COMMUNICATION AND BUFFER
    struct sockaddr_in userverand,userveror;
    int usocketand,usocketor;
    int slenand=sizeof(userverand);
    int slenor=sizeof(userveror);
    int usen,urecv;
    char outbuff[BUFLEN][BUFLEN];  
    char orifile[20][30]={0};
    int i=0;

//UDP SOCKET START.                     COPY ON WEBSITE
    void udpsocketand(void)
    {
	    usocketand=socket(AF_INET,SOCK_DGRAM,0);
	    if(usocketand==-1)
	    {
	     printf("Could not create socket");
	    }
	    memset(&userverand,0,sizeof(userverand));
	    userverand.sin_family = AF_INET;
	    userverand.sin_port = htons(ANDPORT);
    }
    void udpsocketor(void)
    {
	    usocketor=socket(AF_INET,SOCK_DGRAM,0);
	    if(usocketor==-1)
	    {
	     printf("Could not create socket");
	    }
	    memset(&userveror,0,sizeof(userveror));
	    userveror.sin_family = AF_INET;
	    userveror.sin_port = htons(ORPORT);
    }
//UDP SEND
    void udpsand(void)
    {
	usen=sendto(usocketand,orifile[i],30,0,(struct sockaddr *) &userverand,slenand);
        if(usen==-1)
        {
         printf("Error send,holy crap");
        }
	// close(usocketinfo);
    }
    void udpsor(void)
    {
        usen=sendto(usocketor,orifile[i],30,0,(struct sockaddr *) &userveror,slenor);
        if(usen==-1)
        {
         printf("Error send,holy crap");
        }
        // close(usocketinfo);
    }

int main(int argc , char *argv[])
{
  //PARAMETERS OF TCP COMMUNICATION AND BUFFER 
    int socketfd=0;
    int newsocketfd=0;
    int c=0;
    int j=0,k=0,count=0;
    int rec=0;
    char recbuff[BUFLEN]={0};
    //char *recbuff = (char*)malloc(sizeof(char)*BUFLEN);
    struct sockaddr_in server,client;
    char andfile[10][30]={0};
    char orfile[10][30]={0};
    int u=0,v=0,w=0,countand=0,countor=0;
    orifile[20][30]='\0';
    recbuff[BUFLEN]='\0';
    andfile[10][30]='\0';
    orfile[10][30]='\0';
//UDP SOCKET
    udpsocketand();
    udpsocketor();
//SOCKET START.                          COPY ON WEBSITE
//CREATE
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(socketfd==-1)
    {
     printf("Could not create socket");
    }
    memset( &server, 0, sizeof(server) );
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(TCPPORT);
//BIND 
    if(bind (socketfd,(struct sockaddr*)&server,sizeof(server) )<0)
    {
     printf("Error binding, holy crap\n");
     return 1;
    }
    puts("The edge server is up and running.");
//LISTEN
    listen(socketfd,20);
    c=sizeof(client);
    while(1)
    {
	
	memset(&recbuff,0,BUFLEN);
//ACCEPT
    	if( (newsocketfd=accept(socketfd,(struct sockaddr*)&client,(socklen_t*)&c) ) )
    	{
    	 printf("\n");
    	}
//TCP RECEIVE    
	rec=recv(newsocketfd,recbuff,BUFLEN,0);
//	printf("%s ",recbuff);
//	fflush(stdout);
//	puts("\n");
        if(rec==-1)
        {
        	printf("Error receive,holy crap");
        }
//DIVIDED CONTENTS LINE BY LINE
	while(recbuff[k]!='g')//HAVE NOT RECEIVED END MESSAGE 
	{
		count++;

	 for(k;recbuff[k]!='\n';k++)
	 { orifile[j][i]=recbuff[k];i++; }
		k++;
	 	i=0;
	 	j++;
	}
	printf("The edge server has received %d lines from the client using TCP over port %d.\n",count,TCPPORT);//SHOW ON SCREEN
	fflush(stdout);
	//puts("\n");
	while(u<count)//COUNT THE NUMBER OF LINES WITH THE TYPE 'AND' AND 'OR' RESPECTIVELY
	{
		if(orifile[u][0]=='a')
		{
			for(v=0;v<strlen(orifile[u]);v++)
				{
					andfile[countand][v]=orifile[u][v];
				}		
			countand++;
		}
		else
		{
			for(v=0;v<strlen(orifile[u]);v++)
				{
					orfile[countand][v]=orifile[u][v];
				}		
			countor++;
		}
	u++;
	}
	printf("The edge has successfully sent %d lines to Backend-Server OR.\n",countor);//SHOW ON SCREEN
	fflush(stdout);
	//puts("\n");
	printf("The edge has successfully sent %d lines to Backend-Server AND.\n",countand);//SHOW ON SCREEN
	fflush(stdout);
	//puts("\n");
//EXTRACT TWO COMPUTATION NUMBERS LINE BY LINE 
        char d[11][11]={0};
	char e[11][11]={0};
  //      d[10][10]='\0';
  //     e[10][10]='\0';
	int x=0,y=0,k=0,l=0;
        for(k=0;k<count;k++){
	while( l<strlen(orifile[k]) )
	{
	 if(orifile[k][l]==',')
		 {
			l++;
			while(orifile[k][l]!=',')
			{
				d[k][x]=orifile[k][l];
				l++;
				x++;
			}
			l++;
			x=0;
			while((orifile[k][l]>='0')&&(orifile[k][l]<='9'))
			{
				e[k][y]=orifile[k][l];
				l++;
				y++;	
			}
			y=0;
		 }
		 else
		 {
			 l++;
		 } 
		}
		l=0;
	}
 	printf("The edge server starts receiving the computation results from Backend-Server OR and Backend-Server AND using UDP over port %d.\n",UDPPORT);     //SHOW ON SCREEN
	printf("The computation results are:\n");
	puts("\n");
//UDP SEND AND RECEIVE
	for(i=0;i<count;i++)
	{
	  if(orifile[i][0]=='a')
	  {
	   udpsand();
	   if(recvfrom(usocketand,outbuff[i],BUFLEN,0,(struct sockaddr *) &userverand,&slenand)==-1)
            {
             printf("Error send,holy crap");
            }
	   outbuff[i][15]='a';
	  }
	  else if(orifile[i][0]=='o')
	  {
           udpsor();
	   if(recvfrom(usocketor,outbuff[i],BUFLEN,0,(struct sockaddr *) &userveror,&slenor)==-1)
            {
             printf("Error send,holy crap");
            }
	   outbuff[i][15]='o';
	  }      
	}
	char end[1]="e";//END MESSAGE:LET BACKEND SERVER STOP RECEIVING
	sendto(usocketand,end,1,0,(struct sockaddr *) &userverand,slenand);
        sendto(usocketor,end,1,0,(struct sockaddr *) &userveror,slenor);
	for(i=0;i<count;i++)
	{
		if(outbuff[i][15]=='a')
		{
			printf("%s and %s = %s\n",d[i],e[i],outbuff[i]);
			fflush(stdout);
		}
		else if(outbuff[i][15]=='o')
		{
			printf("%s or %s = %s\n",d[i],e[i],outbuff[i]);
			fflush(stdout);
		}
	}//SHOW ON SCREEN
	puts("\n");
	printf("The edge server has successfully finished receiving all computation results from Backend-Server OR and Backend-Server And.\n");
	fflush(stdout);
	printf("The edge server has successfully finished sending all computation results to the client.\n");
	fflush(stdout);
	char mess[1]={'\n'};
//TCP REPLY
	for(i=0;i<count;i++)
        {
        	write( newsocketfd,outbuff[i],strlen(outbuff[i]) );
        	if(newsocketfd<0)
      		 {
      		  printf("Error acception,holy crap");
      		  return 1;
      		 }
		write( newsocketfd,mess,1 );
        	if(newsocketfd<0)
      		 {
      		  printf("Error acception,holy crap");
      		  return 1;
      		 }
        }
	
    //CLOSE
    close(newsocketfd);
    }
    return 0;
}
