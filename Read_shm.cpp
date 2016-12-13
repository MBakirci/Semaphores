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

const int SIZE = 1024;

struct cijfer_t {
    int waarde;
    char uitspraak[10];
};

int main () {
    void *vaddr;
    int shm_fd =0;
    cijfer_t *ct;
    for(;;) {
        /* get shared memory handle */
        if ((shm_fd = shm_open("my_shm", O_CREAT | O_RDWR, 0666)) == -1) {
            perror("cannot open");
            return -1;
        }


    /* set the shared memory size to SHM_SIZE */
    if (ftruncate(shm_fd, SIZE) != 0){
        perror("cannot set size");
        return -1;
    }


        /* Map shared memory in address space. MAP_SHARED flag tells that this is a
        * shared mapping */
        if ((vaddr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED) {
            perror("cannot mmap");
            return -1;
        }


        if (mlock(vaddr, SIZE) != 0) {
            perror("cannot mlock");
            return -1;
        }

            ct = (struct cijfer_t *) vaddr;
            printf("waarde=%d", ct->waarde);
            printf(" uitspraak=%s\n", ct->uitspraak);




        /* unmap from address space */
        munmap(vaddr, SIZE);

        close(shm_fd);

    }

        return 0;
    }
