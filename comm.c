#include "header.h"
int app = 0;

int comm(char *c[], char *p, char *i, char *r, int n) {
  int iput, oput, a = 0;
  iput = dup(STDIN_FILENO);
  oput = dup(STDOUT_FILENO);
  int j, k = 0, l, bg = 0, in, out;
  char *pipe[50];
  while (k < n) {
    for (l = 0, j = k; j < n && strcmp(c[j], "|") != 0; j++, l++)
      pipe[l] = c[j];
    k = j + 1;
    in = indir(pipe, l);
    out = outdir(pipe, l);
    if (in == -2) {
      perror("Multiple Files");
      return 1;
    }
    if (out == -2) {
      perror("Multiple Files");
      return 1;
    }
    if (in == -1 && out != -1)
      l = out - 1;
    else if (in != -1 && out == -1)
      l = in - 1;
    else if (in != -1 && out != -1) {
      if (in < out)
        l = in - 1;
      else
        l = out - 1;
    } else
      ;
    if (in != -1) {
      in = open(pipe[in], O_RDONLY);
      if (in == -1) {
        perror("Invalid File");
        return 1;
      }
      dup2(in, STDIN_FILENO);
    } else {
      if (a++ == 0)
        dup2(iput, STDIN_FILENO);
      else {
        in = open("dummy", O_RDONLY);
        dup2(in, STDIN_FILENO);
      }
    }
    if (out != -1) {
      if (app == 0)
        out = open(pipe[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      else
        out = open(pipe[out], O_WRONLY | O_CREAT | O_APPEND, 0644);
      dup2(out, STDOUT_FILENO);
    } else {
      if (k < n) {
        out = open("dummy", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(out, STDOUT_FILENO);
      } else
        dup2(oput, STDOUT_FILENO);
    }
    pipe[l] = NULL;
    if (strcmp(pipe[0], "cd") == 0)
      cd_fun(pipe, p, i, r, l);
    else if (strcmp(pipe[0], "pwd") == 0)
      pwd_fun(p);
    else if (strcmp(pipe[0], "echo") == 0)
      echo_fun(pipe, l);
    else if (strcmp(pipe[0], "ls") == 0)
      ls_fun(pipe, l);
    else if (strcmp(pipe[0], "pinfo") == 0)
      pinfo_fun(pipe, p, i, l);
    else if (strcmp(pipe[0], "kjob") == 0)
      kjob(pipe, l);
    else if (strcmp(pipe[0], "jobs") == 0)
      jobs(p);
    else if (strcmp(pipe[0], "fg") == 0)
      fg(pipe, l);
    else if (strcmp(pipe[0], "overkill") == 0)
      overkill();
    else if (strcmp(pipe[0], "setenv") == 0)
      seten(pipe, l);
    else if (strcmp(pipe[0], "unsetenv") == 0)
      unseten(pipe, l);
    else if (strcmp(pipe[0], "quit") == 0)
      return 0;
    else {
      if (strcmp(pipe[j - 1], "&") == 0) {
        bg = 1, l = l - 1;
      }
      pipe[l] = NULL;
      exec_cmd(pipe, bg, l);
    }
    if (in != -1)
      close(in);
    if (out != -1)
      close(out);
    app = 0;
  }
  remove("dummy");
  dup2(iput, STDIN_FILENO);
  dup2(oput, STDOUT_FILENO);
  return 1;
}

void exec_cmd(char *c[], int bg, int n) {
  pid_t pid;
  pid = fork();
  if (pid == -1)
    perror("Fork failed");

  else if (pid == 0) {
    setpgid(0, 0);
    if (bg == 0)
      tcsetpgrp(STDIN_FILENO, getpid());
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    int e = execvp(c[0], c);
    if (e == -1) {
      perror("Invalid Command");
    }
    fflush(stdout);
    exit(EXIT_SUCCESS);
  }

  else {
    int status;
    setpgid(pid, pid);
    prinsert(pid, c, n);
    if (bg == 0) {
      tcsetpgrp(STDIN_FILENO, pid);
      waitpid(pid, &status, WUNTRACED);
      tcsetpgrp(STDIN_FILENO, getpid());
      if (WIFEXITED(status))
        prdelete(pid);
    }
  }
}

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
    if (strcmp(parse[i], ">>") == 0 && i < n - 1 && out == -1)
      out = ++i, app = 1;
    else if (strcmp(parse[i], ">") == 0 && i < n - 1 && out == -1)
      out = ++i;
    else if (strcmp(parse[i], ">") == 0 && out != -1)
      out = -2;
    i++;
  }
  return out;
}
