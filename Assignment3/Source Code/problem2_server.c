/**
* @file problem2_server.c
* @brief This file creates a server for file transfer using UDP  
*   The server recieves the  filename and starts reading file 
*   and continues to send a buffer filled with file contents encrypted until file-end is reached.
* @author Anshuman Shakya
*
* @date 8/22/2019
*/

#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
#define IP_PROTOCOL 0 
#define PORT_NO 15050 
#define NET_BUF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 
#define nofile "File Not Found!" 
  
/**
* This function clears buffer
* @author Anshuman Shakya
* @param character b
* @date 8/22/2019
*/ 
void clearBuf(char* b) 
{ 
    int i; 
    for (i = 0; i < NET_BUF_SIZE; i++) 
        b[i] = '\0'; 
} 
  
/**
* function for encryption
* @author Anshuman Shakya
* @param character ch
* @date 8/22/2019
*/
char Cipher(char ch) 
{ 
    return ch ^ cipherKey; 
} 

/**
* function for sending file
* @author Anshuman Shakya
* @param character ch
* @date 8/22/2019
*/  
int sendFile(FILE* fp, char* buf, int s) 
{ 
    int i, len; 
    if (fp == NULL) { 
        strcpy(buf, nofile); 
        len = strlen(nofile); 
        buf[len] = EOF; 
        for (i = 0; i <= len; i++) 
            buf[i] = Cipher(buf[i]); 
        return 1; 
    } 
  
    char ch, ch2; 
    for (i = 0; i < s; i++) { 
        ch = fgetc(fp); 
        ch2 = Cipher(ch); 
        buf[i] = ch2; 
        if (ch == EOF) 
            return 1; 
    } 
    return 0; 
} 
  
/**
* This function is driver function
* @author Anshuman Shakya
* @date 7/31/2019
*/  
int main() 
{ 
    int sockfd, nBytes; 
    struct sockaddr_in addr_con; 
    int addrlen = sizeof(addr_con); 
    addr_con.sin_family = AF_INET; 
    addr_con.sin_port = htons(PORT_NO); 
    addr_con.sin_addr.s_addr = INADDR_ANY; 
    char net_buf[NET_BUF_SIZE]; 
    FILE* fp; 
  
    // socket() 
    sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 
  
    if (sockfd < 0) 
        printf("\nfile descriptor not received!!\n"); 
    else
        printf("\nfile descriptor %d received\n", sockfd); 
  
    // bind() 
    if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0) 
        printf("\nSuccessfully binded!\n"); 
    else
        printf("\nBinding Failed!\n"); 
  
    while (1) { 
        printf("\nWaiting for file name...\n"); 
  
        // receive file name 
        clearBuf(net_buf); 
  
        nBytes = recvfrom(sockfd, net_buf, 
                          NET_BUF_SIZE, sendrecvflag, 
                          (struct sockaddr*)&addr_con, &addrlen); 
  
        fp = fopen(net_buf, "r"); 
        printf("\nFile Name Received: %s\n", net_buf); 
        if (fp == NULL) 
            printf("\nFile open failed!\n"); 
        else
            printf("\nFile Successfully opened!\n"); 
  
        while (1) { 
  
            // process 
            if (sendFile(fp, net_buf, NET_BUF_SIZE)) { 
                sendto(sockfd, net_buf, NET_BUF_SIZE, 
                       sendrecvflag,  
                    (struct sockaddr*)&addr_con, addrlen); 
                break; 
            } 
  
            // send 
            sendto(sockfd, net_buf, NET_BUF_SIZE, 
                   sendrecvflag, 
                (struct sockaddr*)&addr_con, addrlen); 
            clearBuf(net_buf); 
        } 
        if (fp != NULL) 
            fclose(fp); 
    } 
    return 0; 
} 