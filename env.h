void searchenv(char **argv,int count)
{
	char *tmp,*tmp1;
	int i;

	for(i=0;i<count;i++)
	{
		tmp=argv[i];

		if(tmp[0]=='$')
		{
			tmp1=tmp+1;
			tmp1=getenv(tmp1);
			strcpy(tmp,tmp1);
		}


	}

}