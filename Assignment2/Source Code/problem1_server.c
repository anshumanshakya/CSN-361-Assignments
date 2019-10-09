/**
* @file problem1_server.c
* @brief this file creates the server using TCP protocol 
*    and IPv4 address.
*
* @author Anshuman Shakya
*
* @date 7/31/2019
*/

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

/**
* This function will create a socket and bind it to listen to PORT 8080.
* then accepts and send messages to the client
* @author Anshuman Shakya
* @date 7/31/2019
*/
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hi from server"; 
       
    // Creating socket file descriptor 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( server_fd < 0) 
    { 
        printf("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        printf("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    //listening to clients 
    if (listen(server_fd, 3) < 0) 
    { 
        printf("listen failed"); 
        exit(EXIT_FAILURE); 
    } 
    //creating new socket to accept messages from client
    new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen);
    if (new_socket <0) 
    { 
        printf("cannot accept"); 
        exit(EXIT_FAILURE); 
    } 
    //reading message
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    //sending message
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hi sent to client\n"); 
    return 0; 
} 