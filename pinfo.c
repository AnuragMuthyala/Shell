#include "header.h"

void pinfo_fun(char *c[], char *path, char *init, int n) {
  int i = 0, j = 0, k;
  if (n == 1)
    i = getpid();
  else if (n == 2) {
    char *str = c[1];
    for (int l = 0; l < strlen(str); l++)
      i = (i * 10) + (int)(str[l] - '0');
  } else {
    perror("No process id");
  }
  struct stat st;
  char ch[1000];
  char *name = malloc(100 * sizeof(char));
  char *tok;
  char s[20] = "/proc/";
  printf("pid -- %d\n", i);
  while (i > 0) {
    k = i % 10;
    ch[j++] = (char)(k + '0');
    i = i / 10;
  }
  ch[j] = '\0';
  for (j = 0; j < strlen(ch) / 2; j++) {
    char temp = ch[j];
    ch[j] = ch[strlen(ch) - 1 - j];
    ch[strlen(ch) - 1 - j] = temp;
  }
  for (j = 0, k = strlen(s); j < strlen(ch); j++, k++)
    s[k] = ch[j];
  s[k] = '\0';
  j = chdir(s);
  k = open("stat", O_RDONLY);
  fstat(k, &st);
  read(k, ch, 1000);
  tok = strtok(ch, " ");
  j = 0;
  while (j <= 22) {
    if (j == 2)
      printf("Process status -- %s\n", tok);
    else if (j == 22)
      printf("Memory -- %s\n", tok);
    else
      ;
    tok = strtok(0, " ");
    j++;
  }
  readlink("exe", name, 100);
  printf("%s\n", name);
  if (memcmp(name, init, strlen(init)) == 0) {
    ch[0] = '~';
    for (i = 0; i < strlen(name) - strlen(init); i++)
      ch[i + 1] = name[strlen(init) + i];
    ch[i + 1] = '\0';
    for (i = 0; i < strlen(ch); i++)
      name[i] = ch[i];
    name[i] = '\0';
  }
  printf("Executable path -- %s\n", name);
  chdir(path);
}
