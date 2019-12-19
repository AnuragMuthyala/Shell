#include "header.h"

void ls_log(char *s) {
  int d = 0;
  struct stat st;
  struct group *grp;
  struct passwd *pwd;
  if (stat(s, &st) == 0 && S_ISDIR(st.st_mode))
    d = 1;
  if (d == 0)
    lstat(s, &st);
  if (d == 1)
    printf("%c", (S_ISDIR(st.st_mode)) ? 'd' : '-');
  else
    printf("%c", ((st.st_mode & S_IFMT) == S_IFLNK) ? 'l' : '-');
  printf("%c", (st.st_mode & S_IRUSR) ? 'r' : '-');
  printf("%c", (st.st_mode & S_IWUSR) ? 'w' : '-');
  printf("%c", (st.st_mode & S_IXUSR) ? 'x' : '-');
  printf("%c", (st.st_mode & S_IRGRP) ? 'r' : '-');
  printf("%c", (st.st_mode & S_IWGRP) ? 'w' : '-');
  printf("%c", (st.st_mode & S_IXGRP) ? 'x' : '-');
  printf("%c", (st.st_mode & S_IROTH) ? 'r' : '-');
  printf("%c", (st.st_mode & S_IWOTH) ? 'w' : '-');
  printf("%c", (st.st_mode & S_IXOTH) ? 'x' : '-');
  grp = getgrgid(st.st_gid);
  pwd = getpwuid(st.st_uid);
  printf(" %ld", st.st_nlink);
  printf(" %s", grp->gr_name);
  printf(" %s", pwd->pw_name);
  printf(" %9ld", st.st_size);
  char *str = ctime(&st.st_atime);
  int j = 1;
  char *tok = strtok(str, " ");
  while (tok != 0) {
    if (j == 2)
      printf(" %s", tok);
    else if (j == 3)
      printf(" %s ", tok);
    else if (j == 4) {
      for (int i = 0; i <= 4; i++)
        printf("%c", tok[i]);
    } else
      ;
    tok = strtok(0, " ");
    j++;
  }
  printf(" %s\n", s);
}
