/**
* @file problem2.c
* @brief this file creates a parent process 
* and a child process and then a child's child process.
* the parent process exits and child process becomes orphan
* then the child's child process exits and child process keeps running.
* which makes child's child process a zombie process.
*
* @author Anshuman Shakya
*
* @date 7/31/2019
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
  
    int x; 
    x = fork(); 
  
    if (x > 0) 
        printf("In Parent Process\n Parent Process ID : %d\n", getpid()); 
  
    else if (x == 0) { 
        sleep(3); 
        x = fork(); 
  
        if (x > 0) { 
   printf("In Child Process(Orphan) \n Child Process ID :%d\n PARENT PROCESS ID : %d\n", getpid(), getppid()); 
  
   while(1) 
     sleep(1); 
    
    } 
        else if (x == 0) 
            sleep(2);
            printf("In Child's Child's Process(Zombie) \n My Process ID :%d\n My Parent ID : %d\n", getpid(), getppid()); 
    } 
  
    return 0; 
} 