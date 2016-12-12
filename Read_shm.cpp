//
// Created by student on 12-12-16.
//

#include <semaphore.h>
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
    int sem_fd;
    void *vaddr;

    sem_fd = shm_open("my_shm",O_RDONLY, 0666);
    vaddr = mmap(0,SIZE,PROT_READ, MAP_SHARED, sem_fd,0);
    struct cijfer_t* ct;
    ct = (struct cijfer_t*)vaddr;
    printf("%d,%s\n",ct->waarde,ct->uitspraak);
    shm_unlink("my_shm");
    return 0;
}
