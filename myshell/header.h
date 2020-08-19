  #include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

typedef struct running_jobs
{
  char jobName[100];
  pid_t pid;
  struct running_jobs * next;
}running_jobs;

int main(int argc, char **argv);

void displayprompt();
void my_loop(void);
void getdirectory();

//builtin functions
int my_cd(char **args);
int my_pwd(char **args);
int my_echo(char **args);
int my_pinfo(char **args);
int my_jobs();
int my_fg(char ** args);
int my_killallbg();
int my_quit();
int my_kjob(char **args);




int my_execute(char **args);
int commandRun(char **args);
char *my_read_line(void);
char ** my_split_line(char *line);
int my_split_command(char* line);
void sig_chld(int signo);
int my_launch(char **args);
//int add_job(pid_t pid, char * jobName);
int add_job(pid_t pid, char * jobName);
int delete_job(pid_t pid);


void ctrlC();
void ctrlD();
