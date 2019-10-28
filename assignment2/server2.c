#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <sys/wait.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	//Grab the socket, read the message from client, send back message to client after
	printf("Inside new process image to read and send back message to client\n");
	int new_socket = atoi(argv[1]);
	char buffer[1024] = {0};
	char *hello = "Hello from server"; 


	int valread = read( new_socket , buffer, 1024); 
	printf("%s\n",buffer ); 
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	return 0;
}
