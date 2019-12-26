#include "control.h"

int main(int argc, char * argv[]){
  char flag[2];
  strncpy(flag, argv[1], 2);
  us.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;

  if (!strcmp(flag, "-c")){
    creating();
  }
  else if (!strcmp(flag, "-r")){
    removing();
  }
  else if (!strcmp(flag, "-v")){
    viewing();
  }
  else{
    printf("Invalid flag\n");
  }
}

int creating(){
  semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semctl(semd, 0, SETVAL, us);
  printf("semaphore created\n");

  shmd = shmget(SHKEY, SEG_SIZE, IPC_CREAT | 0644);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  printf("shared memory created\n");

  fd = open("semaphone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fd);
  printf("file created\n");
}

int removing(){
  printf("trying to get in\n");
  viewing();

  shmd = shmget(SHKEY, SEG_SIZE, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  printf("shared memory removed\n");

  remove("semaphone.txt");
  printf("file removed\n");

  semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semop(semd, &sb, 1);
  semctl(semd, IPC_RMID, 0);
  printf("semaphore removed\n");
}

int viewing(){
  fd = open("semaphone.txt", O_RDONLY);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  printf("The story so far:\n");
  char buff[SEG_SIZE];
  buff[0] = '\0';
  read(fd, buff, SEG_SIZE);
  if (strlen(buff) != 0) {
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("%s\n",buff);
  close(fd);
}
