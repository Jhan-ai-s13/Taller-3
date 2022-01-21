#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];
  int rn;

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:
	close(fd[WRITE]);
	read(fd[READ], &rn, sizeof(rn));
	if(rn<500) printf("%d -> menor que 500",rn);
	if(rn>=500 && rn<=1000) printf("%d -> mayor o igual a 500",rn);
	exit(0);

  case -1:
	perror("fork() failed)");
	exit(EXIT_FAILURE);

  default:
	close(fd[READ]);
	srand(time(NULL));
	rn = rand() % 1000 + 1;
	write(fd[WRITE], &rn, sizeof(rn));
  }
}