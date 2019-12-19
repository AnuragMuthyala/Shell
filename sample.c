#include "header.h"

void main() {
  int o = open("foo4.txt", O_RDONLY);
  int p = dup(o);
  char str[100];
  read(o, str, 100);
  printf("%s", str);
  read(p, str, 100);
  printf("%s", str);
  close(o);
  close(p);
}
