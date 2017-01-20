//
// Created by student on 13-12-16.
//


#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <signal.h>

#define QUEUE_NAME  "/my_queue"
#define PRIORITY 1
#define SIZE 1024

bool quit = false;
struct cijfer_t {
    int waarde;
    char uitspraak[10];
};

void sigHandler(int sig)
{
    quit = true;
}

int main()
{
    mq_unlink(QUEUE_NAME);
    mqd_t ds;
    struct mq_attr queue_attr;
    cijfer_t ctarray[] ={{0,"Zero"},{1,"One"},{2,"Two"},{3,"Three"},{4,"Four"},{5,"Five"},{6,"Six"}
            ,{7,"Seven"},{8,"Eight"},{9,"Nine"}};
    cijfer_t ct;
    /* Attributes for our queue. Those can be set only during creating. */
    queue_attr.mq_maxmsg = 10;  /* max. number of messages in queue at the same time */
    queue_attr.mq_msgsize = SIZE; /* max. message size */

    /* Creates a new queue named "/my_queue" and opens it for
 * sending and receiving. The queue file permissions are set rw for owner and nothing for group/others.
* Queue limits set to values provided above. */
        if ((ds = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0600, &queue_attr)) == (mqd_t) -1) {
            perror("Creating queue error");
            return -1;
        }
        printf("Opened\n");
        signal(SIGINT,sigHandler);
        /* Send a message to the queue with priority 1.
     * Higher the number, higher is the priority. A high priority message is inserted
     * before a low priority message. First-in First-out for equal priority messages.
    */
        do {
            for(int i= 0;i<10;i++) {
                ct.waarde = ctarray[i].waarde;
                strcpy(ct.uitspraak, ctarray[i].uitspraak);
                printf("waarde=%d", ct.waarde);
                printf(" uitspraak=%s\n", ct.uitspraak);
                if (mq_send(ds, (const char *) &ct, sizeof(ct), 0) == -1) {
                    perror("Sending message error");
                    return -1;
                }
            }

        }while(!quit);


        /* Close queue... */
        if (mq_close(ds) == -1)
            perror("Closing queue error");
    mq_unlink(QUEUE_NAME);



    return 0;

}