//Anshuman Shakya 17114013

#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 


int main() {
    //shared memory for storing process id's of child and parent process together
    int shmid; 
    key_t key = IPC_PRIVATE; 
    int *shm_arr; 

    int length = 7; 
    int parent = getpid();
    
    size_t SHM_SIZE = sizeof(int)*length; 
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    shm_arr = shmat(shmid, NULL, 0);
    
    for(int i=0; i<7; i++) shm_arr[i] = 0;
    shm_arr[6] = getpid();

    for(int i=0; i<2; i++) {
        pid_t pid = fork();
        if(pid != 0) { shm_arr[i] = pid; }
        else {
            for(int j=0; j<2; j++) {
                pid_t pid = fork();
                if(pid == 0) break;
                shm_arr[2*j + 2 + i] = pid;
            }
            break;
        }
    }
    if(parent == getpid()){
        //waiting until array is filled
        for(int i=0; i<7; i++){
            while(shm_arr[i] == 0);
        } 
        printf("process id's of children => %d, %d\n", shm_arr[0], shm_arr[1]);
        printf("process id's of grandchildren => %d, %d, %d, %d\n", shm_arr[2], shm_arr[3], shm_arr[4], shm_arr[5]);
        printf("process id's of parent=> %d\n", shm_arr[6]);
    }
}