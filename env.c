#include "header.h"

void seten(char **parse, int n) {
  if (n == 3)
    setenv(parse[1], parse[2], 1);
  else
    perror("Cannot create the variable");
}

void unseten(char **parse, int n) {
  char *s;
  s = parse[1];
  if (getenv(s) != NULL)
    unsetenv(s);
  else
    perror("No variable exists");
}
