#include <header.h>
extern char *dir;
int make_int(char * str);

//PWD
int my_pwd(char **args)
{
	//getcwd
	char *cwd;
	char home[20]="myshell";
	char absoluteDir[200];
	getcwd(absoluteDir,200);
	cwd=strstr(absoluteDir, home);
	//if cwd=home
	if(strcmp(cwd,home)==0)
		strcpy(cwd,"home");
	else
	{
		char *temp=strtok(cwd ,home);
		strcpy(cwd,"home");
		cwd=strcat(cwd,temp);
	}

	printf("/%s\n",cwd);

	return 1;
}
//END PWD

//ECHO
int my_echo(char **args)
{
	int position=1;
	char *word=args[position];
	for(;(word!=NULL);)
	{
		printf("%s",word);
		position++;
		word=args[position];

	}
	printf("\n");
	return 1;
}
//END ECHO


//CD
int my_cd(char **args)
{
	//no argument
	if(args[1]==NULL)
	{
		printf("Usage: cd dirName\n");
	}

	//cd
	else
	{
		if(!(chdir(args[1])))
		{
			getdirectory();
		}
		else
			fprintf(stderr,"error\n");
	}
	return 1;
}
//END CD

//PINFO
int my_pinfo(char **args)
{
	printf("Pid: %s\n",args[1] );
	if(args[1]!=NULL)
	{
		char infoFile[50],line[100],temp;
		int r,file,j=0;
		strcpy(infoFile,"/proc/");
		strcat(infoFile,args[1]);
		strcat(infoFile,"/status");

		if((file=open(infoFile,O_RDONLY))!=-1)
		{
			while((r=read(file,&temp,sizeof(char)))!=0)
			{
				if(temp!='\n')
				{
					line[j]=temp;
					j++;
				}
				else
				{
					if (strstr(line,"State")!=NULL)
						printf("%s\n",line );
					else if (strstr(line,"VmSize")!=NULL)
						printf("%s\n",line );
					/*else if (strstr(line,"State")!=NULL)
					  printf("%s\n",line );*/
					memset(line,0,sizeof(line));
					j=0;

				}
			}
		}
		//fclose(file);

		//executable file
		strcpy(infoFile,"/proc/");
		strcat(infoFile,args[1]);
		strcat(infoFile,"/cmdline");
		//fclose(file);*/
		FILE* fileex = fopen(infoFile, "r");
		if(fileex)
		{
			printf("Executable file: ");
			while((temp = getc(fileex)) != EOF)
			{
				putchar(temp);
			}
			fclose(fileex);
		}
		printf("\n");
	}

}
//END PINFO


//JOBS
extern running_jobs *rjobs;
int my_jobs()
{
	running_jobs *curr=rjobs;
	int i;
	for (i=1;curr!=NULL;curr=curr->next,i++) {
		printf("[%d] %s [%d]\n",i,curr->jobName,curr->pid);
	}
	return 1;
}
//END JOBS

//FG
int my_fg(char ** args)
{
	pid_t pid=make_int(args[1]),wpid;
	int status;
	do{
		wpid=waitpid(pid, &status,WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status));
}

int make_int(char * str)
{
	int i=0,num=0;
	for(;str[i]!='\0';i++)
	{
		num=num*10+(str[i]-'0');
	}
	return num;
}
//END FG

//KILLALLBG
int my_killallbg()
{
	running_jobs *curr=rjobs;
	for(;curr!=NULL;curr=curr->next)
	{
		pid_t pid=curr->pid;
		kill(pid,SIGQUIT);
	}
}
//KILLALLBG

//QUIT
int my_quit()
{
	exit(0);
	return 0;
}
//END QUIT


//kjob
int my_kjob(char **args)
{
	pid_t pid=make_int(args[1]);
	int sig=make_int(args[2]);
	return kill(pid,sig);
}
//end kjobs
