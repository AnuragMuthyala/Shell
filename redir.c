#include "header.h"
char *parse[20], *b_parse[100];

int indir(char **parse, int n) {
  struct stat s;
  int i = 1, in = -1;
  while (i < n) {
    if (strcmp(parse[i], "<") == 0 && i < n - 1 && in == -1) {
      stat(parse[i + 1], &s);
      if (S_ISREG(s.st_mode) == 1)
        in = ++i;
    } else if (strcmp(parse[i], "<") == 0 && in != -1)
      in = -2;
    i++;
  }
  return in;
}

int outdir(char **parse, int n) {
  struct stat s;
  int i = 1, out = -1;
  while (i < n) {
    if (strcmp(parse[i], ">") == 0 && i < n - 1 && out == -1) {
      stat(parse[i + 1], &s);
      if (S_ISREG(s.st_mode) == 1)
        out = ++i;
    } else if (strcmp(parse[i], "<") == 0 && out != -1)
      out = -2;
    i++;
  }
  return out;
}

int main() {
  int pid;
  int in, out;
  int i = 0, n;
  char str[256], *tok;
  read(0, str, 256);
  tok = strtok(str, " \n");
  while (tok != 0) {
    parse[i++] = tok;
    tok = strtok(0, " \n");
  }
  n = i;
  in = indir(parse, n);
  out = outdir(parse, n);
  printf("%d\n%d\n", in, out);
  in = open(parse[in], O_RDONLY);
  out = open(parse[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  parse[1] = NULL;
  if (in != -1)
    dup2(in, STDIN_FILENO);
  if (out != -1)
    dup2(out, STDOUT_FILENO);
  pid = fork();
  if (pid == 0) {
    i = execvp(parse[0], parse);
  } else {
    wait(NULL);
    close(in);
    close(out);
  }
}

void pip(char **parse, int n) {
  in = indir(parse, n);
  out = outdir(parse, n);
  printf("%d\n%d\n", in, out);
  in = open(parse[in], O_RDONLY);
  out = open(parse[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  parse[in - 1] = NULL;
  if (in != -1)
    dup2(in, STDIN_FILENO);
  if (out != -1)
    dup2(out, STDOUT_FILENO);
}
