#include "control.h"

int main(){
  sb.sem_num = 0;
  sb.sem_op = -1;

  printf("trying to get in\n");
  semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semop(semd, &sb, 1);

  shmd = shmget(SHKEY, SEG_SIZE, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }

  fd = open("semaphone.txt", O_WRONLY | O_APPEND);
  printf("Last addition: %s\n", shmat(shmd, 0, 0));
  char new[SEG_SIZE];
  fgets(next, SEG_SIZE, stdin);
  printf("Your addition: %s\n", new);
  write(fd, new, strlen(new));
  close(fd);
  strcpy(last, next);
  shmdt(last);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
}
