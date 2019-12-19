#include "header.h"

struct node {
  pid_t pid;
  char *s[10];
  int length;
  struct node *link;
} *head = NULL, *tail = NULL, *ptr = NULL, *new = NULL;
int lstsize = 0;

void prinsert(pid_t p, char **str, int n) {
  new = malloc(sizeof(struct node));
  if (new != NULL) {
    new->pid = p;
    for (int i = 0; i < n; i++) {
      new->s[i] = malloc(sizeof(char) * 10);
      strcpy(new->s[i], str[i]);
    }
    new->length = n;
    if (head == NULL)
      head = new, tail = new;
    else
      tail->link = new, tail = new;
    new->link = NULL;
    lstsize++;
  } else
    printf("Process cannot be allocated\n");
}

struct node *prdelete(pid_t p) {
  if (head == NULL || (head == tail && p != head->pid))
    return NULL;
  else if (head == tail && p == head->pid)
    new = head, head = NULL, tail = NULL;
  else {
    new = head;
    while (new->pid != p) {
      if (new == tail)
        break;
      ptr = new, new = new->link;
    }
    if (new == head)
      head = new->link;
    else if (new == tail && p != new->pid)
      return NULL;
    else if (new == tail)
      ptr->link = NULL, tail = ptr;
    else
      ptr->link = new->link;
  }
  lstsize--;
  return new;
}

void jobs(char *path) {
  int i, j, k = 0;
  char p[20] = "/proc/", c[10], st[200], t, *tok;
  if (head == NULL)
    ;
  else {
    for (i = 1, ptr = head; ptr != NULL; i++, ptr = ptr->link) {
      j = ptr->pid;
      while (j > 0) {
        c[k++] = (char)(j % 10) + '0';
        j = j / 10;
      }
      c[k] = '\0';
      for (j = 0; j < strlen(c) / 2; j++)
        t = c[j], c[j] = c[strlen(c) - 1 - j], c[strlen(c) - j - 1] = t;
      k = strlen(p);
      for (j = 0; j < strlen(c); j++, k++)
        p[k] = c[j];
      p[k] = '\0';
      if (chdir(p) != -1) {
        printf("[%d]  ", i);
        tok = "/stat";
        for (j = 0, k = strlen(p); j < strlen(tok); j++, k++)
          p[k] = tok[j];
        p[k] = '\0';
        int pr = open(p, O_RDONLY);
        if (pr == -1)
          printf("Stopped\n");
        else {
          read(pr, st, 200);
          tok = strtok(st, " \n");
          j = 1;
          while (j <= 2) {
            tok = strtok(0, " \n");
            j++;
          }
          if (strcmp(tok, "R") == 0)
            printf("Running\t");
          else if (strcmp(tok, "S") == 0)
            printf("Sleeping\t");
          else
            printf("Stopped\t");
        }
        for (int j = 0; j < ptr->length; j++)
          printf("%s ", ptr->s[j]);
        printf("[%d]\n", ptr->pid);
      }
      k = 0;
      p[6] = '\0';
    }
    chdir(path);
  }
}

int prsearch(int n) {
  int i;
  if (n > lstsize || n <= 0)
    return -1;
  for (i = 1, ptr = head; i < n; i++, ptr = ptr->link)
    ;
  return ptr->pid;
}

void term() {
  pid_t p, c;
  int stat;
  p = waitpid(-1, &stat, WNOHANG);
  c = p;
  while (p != -1 && p != 0) {
    struct node *ptr = NULL;
    ptr = prdelete(c);
    if (ptr != NULL) {
      fprintf(stderr, "%s with pid %d exited", ptr->s[0], ptr->pid);
      free(ptr);
      (WIFEXITED(stat)) ? fprintf(stderr, " normally\n")
                        : fprintf(stderr, " abnormally\n");
      p = waitpid(-1, &stat, WNOHANG);
    }
    if (p == c)
      break;
    else
      c = p;
  }
}

void update(char *path) {
  char s[20] = "/proc/";
  char p[10], t;
  int i, j = 0;
  for (ptr = head; ptr != NULL; ptr = ptr->link) {
    i = ptr->pid;
    while (i > 0) {
      p[j++] = (char)(i % 10) + '0';
      i = i / 10;
    }
    p[j] = '\0';
    for (i = 0, j = j - 1; i < strlen(p) / 2; i++, j--)
      t = p[i], p[i] = p[j], p[j] = t;
    for (i = strlen(s), j = 0; j < strlen(p); i++, j++)
      s[i] = p[j];
    s[i] = '\0';
    if (chdir(s) == -1)
      free(prdelete(ptr->pid));
    s[6] = '\0';
    j = 0;
  }
  chdir(path);
}

void overkill() {
  for (ptr = head; ptr != NULL; ptr = ptr->link) {
    if (checkBG(ptr) == 1) {
      kill(ptr->pid, SIGKILL);
      free(prdelete(ptr->pid));
    }
  }
}

int checkBG(struct node *p) {
  if (checkStatus(p->pid) == 0)
    return 1;
  return 0;
}
