#include "header.h"

int cd_fun(char *parse[], char *p, char *i, char *r, int n) {
  int k;
  if (n == 2) {
    char q[30];
    int l = strlen(parse[1]);
    if (strcmp(parse[1], "~") == 0)
      k = chdir(i);
    else
      k = chdir(parse[1]);
    if (k != 0) {
      perror("Error");
      return 0;
    }
    getcwd(q, 30);
    append(parse[1], p, i, r, n);
  } else if (n == 1) {
    chdir(i);
    append("~", p, i, r, n);
  } else
    perror("Incorrect directory");
}
