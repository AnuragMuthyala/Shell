#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/utsname.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<dirent.h>
#include<time.h>
#include<grp.h>
#include<pwd.h>

int append(char*,char*,char*,char*,int);
int comm(char **,char*,char*,char*,int);
int cd_fun(char **,char*,char*,char*,int);
void pwd_fun(char*);
void echo_fun(char**,int);
void ls_fun(char**,int);
void pinfo_fun(char**,char*,char *,int);
void ls_log(char*);
void exec_cmd(char**,int,int);
void term();
void prinsert(pid_t pid,char **,int);
struct node* prdelete(pid_t);
int num(char*);
void kjob(char**,int);
void jobs(char*);
void fg(char**,int);
void seten(char**,int);
void unseten(char**,int);
void geten(char*);
int prsearch(int);
int indir(char**,int);
int outdir(char**,int);
void update(char*);
void overkill();
int checkBG(struct node*);
int checkStatus(pid_t);
