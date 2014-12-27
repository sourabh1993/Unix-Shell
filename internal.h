int runinternal(char *cmd,char **args)
{
	int x=-1;
	char *ptr;

	ptr=(char*)malloc(200);
	//printf("args[1]:%s\n",args[1] );
	if(!strcmp(cmd,"cd"))
	{
		if(!strcmp(args[1],"-")) strcpy(args[1],prevdir);

		else { getcwd(ptr,200) ; strcpy(prevdir,ptr); }
		x=chdir(args[1]);
	}
	return x;
}