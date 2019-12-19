#include "header.h"

int append(char *s, char *path, char *init, char *r, int n) {
  int k = strlen(r), j = strlen(path), i = 0;
  if (memcmp(s, "/", 1) == 0) {
    for (i = 0; i < strlen(s); i++)
      path[i] = s[i];
    path[i] = '\0';
  } else if (strcmp(s, "..") == 0) {
    j--;
    while (path[j] != '/' && j > 0)
      j--;
    if (j == 0)
      path[++j] = '\0';
    else
      path[j] = '\0';
  } else if (strcmp(s, ".") == 0) {
    return 0;
  } else if (strcmp(s, "~") == 0) {
    for (j = 0; j < strlen(init); j++)
      path[j] = init[j];
    path[j] = '\0';
  } else {
    path[j++] = '/';
    r[k++] = '/';
    for (int i = 0; i < strlen(s); i++) {
      path[j++] = s[i];
      r[k++] = s[i];
    }
    path[j] = '\0';
    r[k] = '\0';
  }
  if (memcmp(path, init, strlen(init)) == 0 && strlen(init) <= strlen(path)) {
    r[0] = '~';
    for (i = 1, j = strlen(init); j < strlen(path); i++, j++)
      r[i] = path[j];
    r[i] = '\0';
  } else
    strcpy(r, path);
  return 0;
}
