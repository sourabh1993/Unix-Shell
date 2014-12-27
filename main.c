#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>

char basedir[200];
char prevdir[200];



#include "ioredirect.h"
#include "stringhandle.h"
#include "internal.h"
#include "env.h"
#include "history.h"
#include "pipe.h"
#include "signalhandle.h"


int main()
{
	char cwd[200],cmdtowrite[200];
	char cmd[200],*temp;
	int len,hiscount=0;

	


	getcwd(basedir,sizeof(basedir));
	strcpy(prevdir,basedir);
	hiscount=inithistory();

	while(1)
	{	
	getcwd(cwd,sizeof(cwd));
	printf("\nMy_Shell:%s$",cwd );
	

	signal(SIGINT,signal_handler1);  
	signal(SIGTSTP,signal_handler1);  
	signal(SIGQUIT,signal_handler1);  

	

	scanf(" %[^\n]s",cmd);


	//fgets(cmd,200,stdin);
	//gets(cmd);

	len=strlen(cmd);

	

	//printf("len:%d\n",len );
	//cmd[len]=' ';
	

	if(!strcmp(cmd,"exit"))break;

	//cmd[len]=' ';
	cmd[len]='\0';
	strcpy(cmdtowrite,cmd);

	
	if(strstr(cmd,"!")!=NULL)
		{
			temp=expandbang(cmd,hiscount);
			strcpy(cmd,temp);
			strcpy(cmdtowrite,cmd);
		}



	runit(cmd);
	

	if(cmdtowrite[0]!='!')
		{	savehistory(cmdtowrite,&hiscount);
		}

	

	
	}

	return 0;
}