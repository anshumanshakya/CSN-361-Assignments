//Anshuman Shakya 17114013

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
 
int main() { 
    char hostbuffer[256]; 
    char *IPbuffer; 
    struct hostent *hostentry; 
    int hostname; 
  
    // To retrieve hostname 
    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    if (hostname == -1) { 
        printf("Error in retrieving hostname");
        exit(1); 
    }
    // To retrieve host information 
    hostentry = gethostbyname(hostbuffer); 
    if (hostentry == NULL) { 
        printf("Error in retrieving host information");
        exit(1); 
    } 
  
    // To convert an Internet network 
    // address into ASCII string 
    IPbuffer = inet_ntoa(*((struct in_addr*) hostentry->h_addr_list[0])); 
    if ( IPbuffer == NULL) { 
        perror("Error in converting Internet network address to ASCII string "); 
        exit(1); 
    }
    printf("Hostname: %s\n", hostbuffer); 
    printf("Host IP: %s\n", IPbuffer); 
  
    return 0; 
} 