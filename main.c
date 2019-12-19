#include "header.h"

char path[100], *parse[100], r[100], *b_parse[300];
char init[100];
int main() {
  int bg = 0, j, k = 0, l = 0, e = 0;
  ssize_t mem;
  struct utsname name;
  uname(&name);
  char *c, *d;
  char t[100];
  char *tok, *b_tok;
  c = getlogin();
  d = name.sysname;
  getcwd(path, 100);
  getcwd(init, 100);
  r[0] = '~';
  r[1] = '\0';
  setpgid(getpid(), getpid());
  tcsetpgrp(STDIN_FILENO, getpid());
  int iput = dup(STDIN_FILENO);
  int oput = dup(STDOUT_FILENO);
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  while (e != 1) {
    dup2(iput, STDIN_FILENO);
    dup2(oput, STDOUT_FILENO);
    term();
    update(path);
    tcsetpgrp(STDIN_FILENO, getpid());
    printf("<%s@%s:%s> ", c, d, r);
    fflush(stdin);
    fflush(stdout);
    do {
      read(0, t, 100);
    } while (mem == -1);
    b_tok = strtok(t, ";");
    while (b_tok != 0) {
      b_parse[k++] = b_tok;
      b_tok = strtok(0, ";");
    }
    while (l < k) {
      tok = strtok(b_parse[l++], " \n");
      int i = 0;
      while (tok != 0) {
        parse[i++] = tok;
        tok = strtok(0, " \n");
      }
      if (i == 0)
        continue;
      fflush(stdin);
      j = comm(parse, path, init, r, i);
      if (j == 0)
        e = 1;
    }
    l = 0, k = 0;
    printf("\n");
  }
  return 0;
}
