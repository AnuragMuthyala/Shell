#include "header.h"

void ls_fun(char *parse[], int n) {
  DIR *d;
  char *str;
  struct dirent *sd;
  struct stat s;
  int l_f = 0, a_f = 0, d_f = 0;
  if (n > 1 && n <= 4) {
    for (int i = 1; i < n; i++) {
      if (strcmp(parse[i], "-l") == 0)
        l_f = 1;
      else if (strcmp(parse[i], "-a") == 0)
        a_f = 1;
      else if (strcmp(parse[i], "-la") == 0 || strcmp(parse[i], "-al") == 0)
        l_f = 1, a_f = 1;
      else if ((stat(parse[i], &s) == 0) && S_ISDIR(s.st_mode) && d_f != 1) {
        str = parse[i];
        d_f = 1;
      } else
        ;
    }
  }
  if (d_f == 0)
    d = opendir("./");
  else {
    if (strcmp(str, "..") == 0)
      d = opendir("./..");
    else
      d = opendir(str);
  }
  if (l_f == 0) {
    while ((sd = readdir(d)) != NULL)
      if ((sd->d_name)[0] == '.' && a_f == 0)
        ;
      else
        printf("%s\n", sd->d_name);
  } else {
    while ((sd = readdir(d)) != NULL) {
      if ((sd->d_name)[0] == '.' && a_f == 0)
        ;
      else
        ls_log(sd->d_name);
    }
  }
}
