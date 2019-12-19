#include "header.h"

void echo_fun(char *parse[], int n) {
  int i, j;
  for (i = 1; i < n; i++) {
    if (parse[i][0] == '$') {
      for (j = 0; j < strlen(parse[i]) - 1; j++)
        parse[i][j] = parse[i][j + 1];
      parse[i][j] = '\0';
      if (getenv(parse[i]) == NULL) {
        perror("No environment variable");
        return;
      } else
        printf("%s ", getenv(parse[i]));
    } else
      printf("%s ", parse[i]);
  }
  printf("\n");
}
