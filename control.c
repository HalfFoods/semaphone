#include "control.h"

int semd, v, r, shmd, fd;
char * data;
struct sembuf sb;
union semun us;

int main(int argc, char * argv[]){
  char flag[2];
  strncpy(flag, argv[1], 2);
  us.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("flag is %s\n", flag);

  if (!strcmp(flag, "-c")){
    semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
      printf("error %d: %s\n", errno, strerror(errno));
      semd = semget(SEMKEY, 1, 0);
      v = semctl(semd, 0, GETVAL, 0);
      printf("semctl returned: %d\n", v);
    }
    semctl(semd, 0, SETVAL, us);
    printf("semaphore created\n");

    shmd = shmget(SHKEY, SEG_SIZE, IPC_CREAT | 0644);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
    }
    data = shmat(shmd, 0, 0);
    printf("shared memory created\n");

    fd = open("semaphone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    close(fd);
    printf("file created\n");
  }
  else if (!strcmp(flag, "-r")){
    semd = semget(SEMKEY, 1, 0);
    if (semd == -1) {
      printf("error %d: %s\n", errno, strerror(errno));
    }

    printf("trying to get in\n");
    semop(semd, &sb, 1);

    shmd = shmget(SHKEY, 1, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
    }

    char story[SEG_SIZE];
    read(fd, story, SEG_SIZE);
    printf("The story so far:\n%s\n", story);
    close(fd);

    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory removed\n");
    semctl(semd, IPC_RMID, 0);
    printf("semaphore removed\n");
    remove("semaphone.txt");
    printf("file removed\n");
  }
  else if (!strcmp(flag, "-v")){
    fd = open("semaphone.txt", O_RDONLY);
    if (fd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
    }

    char story[SEG_SIZE];
    read(fd, story, SEG_SIZE);
    printf("The story so far:\n%s\n", story);
    close(fd);
  }
  else{
    printf("Invalid flag\n");
  }
}

int creating(){
  return 0;
}

int removing(){
  return 0;
}

int viewing(){
  return 0;
}
