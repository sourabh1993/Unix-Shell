char** tokenizecmd(char *arg,int *count,char seperator)	
{
	char **argv,args[100];
	int k=0,ind,j=0,len;


	argv=(char**)malloc(20*sizeof(char*));

	len=strlen(arg);



	for(ind=0;ind<len;ind++)
	{

		if(arg[ind]==92)		// Managing escape character 
		{
			
			if(seperator=='|')args[j++]=arg[ind];

			args[j++]=arg[ind+1];
			ind++;
			continue;
		}

		

		if(arg[ind]=='"')
		{
			if(seperator=='|')args[j++]=arg[ind];
			ind++;
			for(;arg[ind]!='\0' && arg[ind]!='"';ind++)
			{
					if(arg[ind]==92)ind++;	
					args[j++]=arg[ind];
			}
			//printf("in\n");
			if(seperator=='|')args[j++]=arg[ind];
				continue;
			//strcpy(argv[k],args);	
				
		}

		if(arg[ind]=='\'')
		{
			if(seperator=='|')args[j++]=arg[ind];
			ind++;
			for(;arg[ind]!='\0' && arg[ind]!='\'';ind++)
				{
					if(arg[ind]==92)ind++;	
					args[j++]=arg[ind]; 
				}

				//printf("(in)\t");
				//printf("{{%s}}\n",args );
				//strcpy(argv[k],args);	
				if(seperator=='|')args[j++]=arg[ind];

				
				//printf("args:%s\n",args );
				continue;
				
		}
		
		if(arg[ind]==seperator  || arg[ind]=='\0')
		{
			args[j]='\0';
			
			if(j!=0)// && args[j-1]!=seperator)
			{argv[k]=(char*)malloc(20);	
			strcpy(argv[k],args);
			//printf("[%s]:",args );
			k++;}
			j=0;
			
		}
		else	
		{
			args[j++]=arg[ind];
		}

		//printf("stuck %d  %d\n",ind,len);
		
	}


	//printf("\narg:%s   j=%d\n",arg,j );
	if(j!=0)
	{
			args[j]='\0';
			argv[k]=(char*)malloc(200);	
			strcpy(argv[k],args);
			//printf("[%s]:",args );
			k++;
	}


	//printf("\n");
	*count=k;

	return argv;


}