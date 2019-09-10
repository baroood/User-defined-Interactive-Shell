void othfunc(char *str,int ptr)
{
	char* args[1024],flag_bg=0,i=0;
	char* token;
	char* qwerty=str;
	while((token=strtok_r(qwerty," ",&qwerty)))
	{
		if(!strcmp(token,"&"))
		{
			flag_bg=1;
		}
		else
		{
			args[i]=token;
			i++;
		}
	}
	args[i]=NULL;
	pid_t pid=fork();
	int status;
	if(flag_bg==1)
	{
		if(pid==0)
		{
			if(execvp(args[0],args)<0)
				perror("error");
		}
		else
		{
			signal(SIGCHLD,handler);
		}
	}
	else
	{
		if(pid==0)
		{
			if(execvp(args[0],args)<0)
				perror("error");
		}
		else
		{
			waitpid(pid,&status,0);
		}
	}
}