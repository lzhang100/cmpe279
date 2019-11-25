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
	printf("Inside new process image to chroot to empty directory and send back file message to client\n");
	//chdir("/empty");
	if(chroot("./empty") != 0){
		perror("chroot failed");
		exit(EXIT_FAILURE); 
	}else{
		printf("chroot succeed\n");
	}


	uid_t id = 65534;
	//Set uid to nobody user
	if(setuid(id) == 0){
		printf("Child: The real user ID after setting setuid is %d\n", getuid());
	}else{
		perror("setuid failed");
		exit(EXIT_FAILURE); 
	}
	int new_socket = atoi(argv[1]);
	char buffer[1024] = {0};
	//char *hello = "Hello from server"; 


	int valread = read( new_socket , buffer, 1024); 
	printf("%s\n",buffer );

	int fd = atoi(argv[2]);
	char readBuffer[20] = {0};
	int rfd = read(fd, readBuffer, 20);
	//printf("%ld\n", strlen(readBuffer));

	send(new_socket , readBuffer, strlen(readBuffer) , 0 ); 
	printf("Hello message sent\n"); 
	return 0;
}
