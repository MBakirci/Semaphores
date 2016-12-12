#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/mman.h>

struct cijfer_t {
  int waarde;
  char *uitspraak;
};

const int SIZE = 1024;
const char SHM_NAME[] = "/my_shm";
struct cijfer_t cijfertjes[10] = {
    {0, (char *)"zero"},  {1, (char *)"one"},   {2, (char *)"two"},
    {3, (char *)"three"}, {4, (char *)"four"},  {5, (char *)"five"},
    {6, (char *)"six"},   {7, (char *)"seven"}, {8, (char *)"eight"},
    {9, (char *)"nine"},
};
int main() {
  int shm_fd = 0;
  void *vaddr = NULL;

  shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    std::cout << "failed to open shm" << std::endl;
    sem_unlink(SHM_NAME);
    return 1;
  }
  std::cout << "opend\n";
  if (ftruncate(shm_fd, SIZE) != 0) {
    std::cout << "Failed to resize the shared memory object\n";
    return 1;
  }
  std::cout << "resized\n";
  vaddr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (vaddr == MAP_FAILED) {
    std::cout << "Failed to mmap() the shared memory object\n";
    return 1;
  }
  std::cout << "mapped\n";
  // mlock(vaddr, SIZE);

  // shm_unlink(SHM_NAME);
  sem_init((sem_t *)vaddr, 1, 1);
  std::cout << "init\n";
  /*** Shared memory is ready for use ***/
  for (int i = 0; i < 10; i++) {
    if (sem_wait((sem_t *)vaddr) == 0) {
      vaddr += cijfertjes[i].waarde;
      sem_post((sem_t *)vaddr);
    }
  }
  munmap(vaddr, SIZE);
  close(shm_fd);
  shm_unlink(SHM_NAME);

  return 0;
}
