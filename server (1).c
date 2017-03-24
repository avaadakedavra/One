#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define _GNU_SOURCE
void get_popen();
  int welcomeSocket, newSocket,recvSocket;
  char buffer[80];
int main(){
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
//  strcpy(buffer,"Hi joel\n");
//  send(newSocket,buffer,20,0);
		system("ls >list.txt");
		system("echo EOF  >> list.txt");

	get_popen();

	close(newSocket);

  		return 0;
 }
	
	void get_popen()
	{
	
		FILE *pf;
		char command[1024];
		char data[80];
		
		sprintf(command,"ps aux wwwf");
		
		pf=fopen("list.txt","r");
		
		while(fgets(data, 80, pf)!=NULL)
		{
			send(newSocket,data,80,0);
		}
		fclose(pf);


	       // Client chose File
		recv(newSocket,buffer,80,0);
		printf("Client chose %s\n",buffer);		

		printf("Sending client %s ..... \n",buffer);

		pf=fopen(buffer,"r");
		
		while(fgets(data, 80, pf)!=NULL)
		{
			send(newSocket,data,80,0);
		}
		fclose(pf);

	}
	
	
	
		
	
	
	
	
