#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void check_error(){
  if (errno != 0){
    printf("Error %d: %s\n",errno,strerror(errno));
    exit(1);
  }
}

static void sighandler(int signo) {
  if (signo == SIGINT){
    int fd = open("log.txt",O_CREAT | O_APPEND | O_RDWR, 0666);
    check_error();

    char err_message[55];
    sprintf(err_message,"The process with pid %7d has exited due to SIGINT\n",getpid());

    write(fd,err_message,55);
    check_error();

    close(fd);
    exit(1);
  }
  if (signo == SIGUSR1) {
    printf("The parent process's pid is %d\n",getppid());
  }
}

int main() {
  signal(SIGINT,sighandler);
  signal(SIGUSR1,sighandler);



  while(1){
    printf("My process ID is: %d\n",getpid());
    sleep(1);
  }

  return 0;
}
