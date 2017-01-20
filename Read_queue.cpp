#include <stdio.h>
#include <mqueue.h>
#include <signal.h>
#include <time.h>

#define QUEUE_NAME "/my_queue"
#define PRIORITY 1
#define SIZE 1024

bool quit = false;

void sigHandler(int sig);

struct cijfer_t {
  int waarde;
  char uitspraak[10];
};

int main() {
  mqd_t ds;
  struct cijfer_t ct;
  /*	struct mq_attr attr, old_attr; */
  unsigned int prio;

  /* Open "/my_queue" for sending and receiving. No blocking when receive a
   * message(O_NONBLOCK).
   * The queue file permissions are set rw for owner and nothing for
   * group/others.
  */
  if ((ds = mq_open(QUEUE_NAME, O_RDWR, 0600, NULL)) == (mqd_t)-1) {
    perror("Creating queue error");
    return -1;
  }

  signal(SIGINT, sigHandler);
  /* Now receive the message from queue. This is a blocking call. Priority of
   * message
   * received is stored in prio.The function receives the oldest of the highest
   * pri-
   * ority message(s) from the message queue. If the size of the buffer,
   * specified
   * by the msg_len argument, is less than the  mq_msgsize attribute of the
   * message queue
   * the function shall fail and return an error
  */
  while (!quit) {
    struct timespec ts = {time(0) + 5, 0};
    if (mq_timedreceive(ds, (char *)&ct, SIZE, 0, &ts) == -1) {
      perror("cannot receive");
      return -1;
    } else {
      printf("waarde=%d", ct.waarde);
      printf(" uitspraak=%s\n", ct.uitspraak);
    }
  }

  /* Close queue... */
  if (mq_close(ds) == -1) perror("Closing queue error");

  return 0;
}

void sigHandler(int sig) { quit = true; }