// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <sys/wait.h> 
#define PORT 8080
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
int main(int argc, char const *argv[]) 
{
    if(argc != 3){
        printf("%s\n", "Usage: sudo ./server PORT_NUM file.txt");
        exit(1);
    }   
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    uid_t id = 65534;

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
      &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(atoi(argv[1])); 

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
       sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
     (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }

    //create file descriptor, open file
    int fd = open("file.txt", O_RDONLY);

    if(fd < 0){
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    char passfp[12];
    sprintf(passfp, "%i", fd);

    if(fork() == 0){
        char pipe_readend[12];
        sprintf(pipe_readend, "%i", new_socket);
        char * argv_list[] = {"./server2", pipe_readend, passfp,NULL}; 
        if(execvp("./server2", argv_list) == -1){
            perror("execvp failed");
            exit(EXIT_FAILURE); 
        }
        
    }else{
        wait(NULL);
        printf("Parent: The real user ID is %d\n", getuid());
    }


    return 0; 
} 
