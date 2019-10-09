/**
* @file problem1_client.c
* @brief this file creates the client using TCP protocol 
*    and IPv4 address and connects to the localhost.
*
* @author Anshuman Shakya
*
* @date 7/31/2019
*/

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

/**
* This function will create a socket and bind it to listen to PORT 8080.
* then accepts and send messages to the client
* @author Anshuman Shakya
* @param chrData The character to print
* @date 7/31/2019
*/
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hi from client"; 
    char buffer[1024] = {0}; 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock< 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address \n"); 
        return -1; 
    } 
   // connecting to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    //sending message
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hi sent to server\n");
    //reading message 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 