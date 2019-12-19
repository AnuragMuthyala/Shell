#include "header.h"

void kjob(char **parse, int n) {
  int p;
  int signum = num(parse[2]);
  int pid = prsearch(num(parse[1]));
  if (pid == -1) {
    perror("No job exists");
    return;
  }
  kill(pid, signum);
  p = waitpid(pid, NULL, WNOHANG);
  free(prdelete(pid));
}

int num(char *s) {
  int i = 0;
  for (int l = 0; l < strlen(s); l++)
    i = (i * 10) + (int)(s[l] - '0');
  return i;
}

void fg(char **parse, int n) {
  int i = num(parse[1]);
  int status;
  pid_t pid = prsearch(i);
  if (pid == -1) {
    perror("No job exists");
    return;
  }
  tcsetpgrp(STDIN_FILENO, pid);
  kill(pid, SIGCONT);
  waitpid(pid, &status, WUNTRACED);
  if (WIFEXITED(status))
    free(prdelete(pid));
}

void bg(char **parse, int n) {
  int i = num(parse[1]);
  int status;
  pid_t pid = prsearch(i);
  if (pid == -1) {
    perror("NO job exists");
    return;
  }
  kill(pid, SIGCONT);
}

int checkStatus(pid_t p) {
  char s[20] = "/proc/", c[10], t, *tok, st[200];
  int i, j = 0;
  i = p;
  while (i > 0) {
    c[j++] = (char)(i % 10) + '0';
    i = i / 10;
  }
  c[j] = '\0';
  for (i = 0; i < strlen(s) / 2; i++)
    t = c[i], c[i] = c[strlen(c) - 1 - i], c[strlen(c) - 1 - j] = t;
  for (i = 0, j = strlen(s); i < strlen(c); i++, j++)
    s[i] = c[j];
  s[i] = '\0';
  tok = "/stat";
  for (j = 0; j < strlen(tok); j++)
    s[i] = tok[j];
  s[i] = '\0';
  int pr = open(s, O_RDONLY);
  if (pr == -1)
    return 0;
  else {
    read(pr, s, 200);
    j = 1;
    tok = strtok(s, " \n");
    while (j++ <= 2)
      tok = strtok(0, " \n");
    if (strcmp(tok, "R") == 0)
      return 1;
    else
      return 0;
  }
}
