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
  char * old = shmat(shmd, 0, 0);
  printf("Last addition: %s\n", old);
  char new[SEG_SIZE];
  printf("Your addition: ");
  fgets(new, SEG_SIZE, stdin);
  printf("\n");
  write(fd, new, strlen(new));
  close(fd);
  strcpy(old, new);
  shmdt(old);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
}
