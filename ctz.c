#include "header.h"

void exec();
int pgid, ppgid;

void sighandler(int signum) {
  kill(pgid, SIGSTOP);
  printf("\nHere..\n");
}

void main() {
  char str[10] = "hello";
  printf("%d\n", getpid());
  while (strcmp(str, "exit") != 0) {
    exec();
    printf("\n>>");
    scanf("%s", str);
  }
}

void exec() {
  int pid;
  pid = fork();
  if (pid == 0) {
    signal(SIGTSTP, SIG_DFL);
    setpgid(getpid(), getpid());
    tcsetpgrp(STDIN_FILENO, getpid());
    char **parse = {"vim", NULL};
    execvp(parse[0], parse);
  } else {
    int status;
    int i = waitpid(pid, &status, WUNTRACED | WNOHANG);
    printf("%d\n", i);
  }
}
