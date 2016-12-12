//
// Created by student on 12-12-16.
//
#include "semaphore.h"
#include "stddef.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

const int SIZE = 4096;

struct cijfer_t {
    int waarde;
    char *uitspraak;
};

int main () {
    sem_t* sem_fd;
    void *vaddr;
    int shm_fd = 0;

    sem_fd = sem_open("my_shm",O_CREAT,S_IRUSR, 100);
    if(sem_fd == SEM_FAILED)
    {
        printf("Failed to open shared memory object");
    }
    // get shared memory handle
    if ((shm_fd = shm_open("my_shm", O_CREAT | O_RDWR, 0666)) == -1){
        perror("cannot open");
        return -1;
    }
    /* lock the shared memory */
    if (mlock(vaddr, SIZE) != 0){
        perror("cannot mlock");
        return -1;
    }
    vaddr = mmap(0,SIZE,PROT_READ, MAP_SHARED, shm_fd,0);
    struct cijfer_t* ct;
    ct = (struct cijfer_t*)vaddr;
    printf("%d,%s\n",ct->waarde,ct->uitspraak);
    sem_unlink("my_shm");
    return 0;
}
