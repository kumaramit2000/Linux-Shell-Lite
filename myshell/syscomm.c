#include <header.h>

int chldrun=0;

void sig_chld(int signo)
{
	chldrun=0;
	pid_t pid;
	int stat;
	pid=wait(&stat);
	if(pid==-1)
		return;
	printf("Process with pid %d terminated\n",pid);
	delete_job(pid);
	//write(STDOUT_FILENO,"exited",40);
	return;
}

int my_launch(char **args)
{
	pid_t pid,wpid;
	int status;
	if(chldrun==0){
		signal(SIGCHLD, sig_chld);
		chldrun=1;}
	pid=fork();

	//childprocess
	if(pid==0)
	{
		if(execvp(args[0],args)==-1)
			fprintf(stderr,"error executing the command\n");
		chldrun=0;
	}
	//couldn't fork
	else if(pid<0)
	{
		fprintf(stderr,"error: fork\n");
		chldrun=0;
	}

	//parent process
	else
	{
		add_job(pid,args[0]);
		int i;
		//search if '&' is given as an argument
		for(i=0;args[i]!=NULL || args[i]!='\0';i++)
		{
			if(strcmp(args[i],"&")==0)
			{
				//chldpid=pid;
				return 1;
			}
		}
		/*	if(waitpid(pid,NULL,WNOHANG))
			return 1;
		 */	do{
			 wpid=waitpid(pid, &status,WUNTRACED);
		 }while(!WIFEXITED(status) && !WIFSIGNALED(status));
		chldrun=0;
				}
	return 1;

}
running_jobs *rjobs=NULL;
int add_job(pid_t pid, char * name)
{
	running_jobs *new=(running_jobs*)malloc(sizeof(running_jobs));
	new->pid=pid;
	strcpy(new->jobName,name);
	new->next=NULL;
	if (rjobs==NULL)
	{
		rjobs=new;
	}
	else
	{
		running_jobs *temp=rjobs;

		for (;temp->next!=NULL;temp=temp->next);
		temp->next=new;
	}
}

int delete_job(pid_t pid)
{
	if (rjobs==NULL) {
		return 1;
	}
	if (rjobs->pid==pid) {
		running_jobs *del=rjobs;
		rjobs=rjobs->next;
		free(del);
		return 0;
	}
	running_jobs *temp=rjobs,*prev;
	for (prev=rjobs;temp->pid!=pid || temp==NULL;temp=temp->next)
	{
		if (temp!=rjobs) {
		prev=prev->next;
	}
	}
	//running_jobs *del=temp->next;
	if(temp!=NULL)
	{
	prev->next=temp->next;
	free(temp);
}
}
