void savehistory(char *cmd,int *count)
{
	int fd;
	char fname[200];

	strcpy(fname,basedir);
	strcat(fname,"/history");

	fd=open(fname,O_CREAT | O_APPEND | O_WRONLY , S_IRUSR | S_IWUSR);

	
	//printf("writing %s\n",cmd );
	write(fd,cmd,strlen(cmd));
	write(fd,"\n",1);

	close(fd);

	(*count)++;
}



void showhistory()
{
	char fname[200];
	int num=1;

	strcpy(fname,basedir);
	strcat(fname,"/history");
	char cmdbuffer[150];
	FILE *fp;
	fp=fopen(fname,"r");
	if(fp==NULL)return;
	//fd=open("history", O_RDONLY);

	while(fgets(cmdbuffer,150,fp) !=NULL)
	{
		printf("%d\t%s",num++,cmdbuffer);
	}

	fclose(fp);
}



// Searches the command by name in history
char* getbyname(char *key)
{
	char *cmd,*finalcmd;
	char fname[200];
	int len,found=0;

	strcpy(fname,basedir);
	strcat(fname,"/history");
	char *cmdbuffer;
	FILE *fp;
	fp=fopen(fname,"r");
	if(fp==NULL)return NULL;
	//fd=open("history", O_RDONLY);

	finalcmd=(char*)malloc(200);
	cmdbuffer=(char*)malloc(200);

	while(fgets(cmdbuffer,150,fp) !=NULL)
	{
		cmd=strtok(cmdbuffer,"|");
		len=strlen(cmd);
		cmd[len-1]='\0';
		
		if(strstr(cmd,key)!=NULL) { strcpy(finalcmd,cmdbuffer); found=1; }
		
	}

	free(cmdbuffer);
	fclose(fp);
	if(found==1)return finalcmd;

	return NULL;
}


char* bangbang(char *cmd,int hcount)
{
	int x=0,i;
	char *occ;
	char *cmdbuffer;
	char fname[200];
	int isnumber=1;

	strcpy(fname,basedir);
	strcat(fname,"/history");

	occ=strstr(cmd,"!");


	for(i=1;occ[i]!='\0';i++)
	{
		if(occ[1]=='-')continue;
		if(!isdigit(occ[i])) { isnumber=0;break;}
	}


	if(cmd[occ-cmd+1]=='!')x=-1;
	else x=atoi(occ+1);

	if(isnumber==0)
	{
		cmdbuffer=getbyname(occ+1);
		return cmdbuffer;
	}

	if(x<0)x=hcount+x+1;

	//printf("x=%d\n",x);
	cmdbuffer=(char*)malloc(150);
	
	FILE *fp;
	fp=fopen(fname,"r");
	if(fp==NULL)return NULL;

	while(fgets(cmdbuffer,150,fp) !=NULL)
	{
		x--;
		if(x==0){break;}
	}

	fclose(fp);

	for(i=0;cmdbuffer[i]!='\0' && cmdbuffer[i]!='\n';i++);
	cmdbuffer[i]='\0';

	if(x==0)return cmdbuffer;
	return NULL;

}


char* expandbang(char *cmd,int hiscount)
{
	char *argvp[20], *bangcmd , *temp;
	char *finalcmd;
	int countpipe=0,i;

	while(1)										// Tokenize the whole command
	{
		argvp[countpipe]=(char*)malloc(50);
		if(countpipe==0) argvp[countpipe]=strtok(cmd,"|");
		else argvp[countpipe]=strtok(NULL,"|");

		if(argvp[countpipe]==0)break;
		countpipe++;		

		if(strstr(argvp[countpipe-1],"!")!=NULL)
		{
			countpipe--;
			bangcmd=(char*)malloc(80);

			strcpy(bangcmd,argvp[countpipe]);

			bangcmd=bangbang(bangcmd,hiscount);

			if(bangcmd==0)break;

			while((temp=strsep(&bangcmd,"|"))!=NULL)
			{
				argvp[countpipe++]=temp;
			}

		}

	}

	finalcmd=(char*)malloc(150);
	strcpy(finalcmd,argvp[0]);

	for(i=1;i<countpipe;i++)
	{
		strcat(finalcmd,"|");
		strcat(finalcmd,argvp[i]);
	}

	return finalcmd;
}


int inithistory()
{
	char fname[200];
	int count=0;

	strcpy(fname,basedir);
	strcat(fname,"/history");
	char cmdbuffer[150];
	FILE *fp;
	fp=fopen(fname,"r");
	if(fp==NULL)return 0;

	while(fgets(cmdbuffer,150,fp) !=NULL)
	{
		count++;
	}

	fclose(fp);
	return count;
}