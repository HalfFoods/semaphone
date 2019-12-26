#include "control.h"

int semd, v, r;

int main(int argc, char * argv[]){
  char flag[2];

  strncpy(flag, argv[1], 2);

  if (!strcmp(flag, "-c")){
    create();
  }
  if (!strcmp(flag, "-v")){

  }
  if (!strcmp(flag, "-r")){

  }
  else{
    printf("Invalid flag\n");
  }
}

void create(){
  semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(SEMKEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0);
    printf("semctl returned: %d\n", v);
  }
  else {
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
    printf("semctl returned: %d\n", r);
  }
  printf("semaphore created\n");
}
