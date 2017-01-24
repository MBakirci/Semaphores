#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.h"
#include "stddef.h"
#include "stdio.h"

typedef struct {
  int waarde;
  char uitspraak[10];
} cijfer_t;

typedef struct {
  cijfer_t buf[1];
  cijfer_t in;
  cijfer_t out;
  sem_t full;
  sem_t empty;
  pthread_mutex_t mutex;
} package_t;

cijfer_t ctarray[] = {{0, "Zero"},  {1, "One"},  {2, "Two"}, {3, "Three"},
                      {4, "Four"},  {5, "Five"}, {6, "Six"}, {7, "Seven"},
                      {8, "Eight"}, {9, "Nine"}};

package_t shared;

void *Producer() {
  int i;
  cijfer_t item;
  for (;;) {
    for (i = 0; i < 10; i++) {
      /* Produce item */
      item = ctarray[i];

      sem_wait(&shared.empty);
      pthread_mutex_lock(&shared.mutex);

      //   Apend()
      shared.buf[0] = item;
      shared.in = ctarray[i];
      printf("Producing: waarde: %d uitspraak: %s\n", item.waarde,
             item.uitspraak);
      fflush(stdout);

      pthread_mutex_unlock(&shared.mutex);
      sem_post(&shared.full);
      usleep(500);
    }
  }
  return NULL;
}

void *Consumer() {
  int i;
  cijfer_t item;

  for (;;) {
    for (i = 10; i > 0; i--) {
      sem_wait(&shared.full);
      pthread_mutex_lock(&shared.mutex);

      //   Take
      item = ctarray[i];
      item = shared.buf[0];
      shared.out = ctarray[i];
      printf("Consuming: waarde: %d uitspraak: %s\n", item.waarde,
             item.uitspraak);
      fflush(stdout);

      pthread_mutex_unlock(&shared.mutex);
      sem_post(&shared.empty);
      usleep(500);
    }
  }
  return NULL;
}

int main() {
  pthread_t producure, consumer;
  int index;

  sem_init(&shared.full, 0, 0);
  sem_init(&shared.empty, 0, 1);
  pthread_mutex_init(&shared.mutex, NULL);

  /* Create a new producer */
  pthread_create(&producure, NULL, Producer, 1);

  /*create a new Consumer*/
  pthread_create(&consumer, NULL, Consumer, 1);

  pthread_exit(NULL);
}