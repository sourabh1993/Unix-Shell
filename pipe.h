void runit(char *cmd)
{
	pid_t pid;
	int x;
	char **argv,**argvp;
	int countfl=0,countpipe=0,i,j;
	int pipes[80][2];
	int ipfile,opfile;
	
	

		argvp=tokenizecmd(cmd,&countpipe,'|');		// Tokenize the whole command
		//printf("countpipe:%d\n",countpipe );
		
	

	for(i=0;i<countpipe;i++)
	{
		pipe(pipes[i]);
	}		

	for(i=0;i<countpipe;i++)
	{
		//printf("argvp[%d]:%s\n",i,argvp[i]);

		countfl=0;

		//printf("argvp[%d] : %s\n",i,argvp[i] );
		argv=(char**)malloc(20*sizeof(char*));

											
		
		ipfile=-1;
		opfile=-1;

	//	if(!strcmp(argvp[i],"bash "))
	//		strcpy(argvp[i],"./a.out");

		ioredirections(&argvp[i],&ipfile,&opfile);
		argv=tokenizecmd(argvp[i],&countfl,' ')	;	// Tokenize the individual commands of pipe
//			printf("countfl: %d\n",countfl);

		

		//ioredirection(argvp[i],&ipfile,&opfile);
		//printf(" %s:\n",argvp[i] );

		pid=fork();
		if(pid==-1)return;
		if(pid==0)									// Run each individual cmd in a newly created process
		{
			

			if(i==0 && i<countpipe-1)dup2(pipes[i][1],1);
			else if(i>0)
			{
				dup2(pipes[i-1][0],0);  
				if(i<countpipe-1) {dup2(pipes[i][1],1); }
			}


			if(ipfile!=-1)  { dup2(ipfile,0); close(ipfile); }
			if(opfile!=-1)  { dup2(opfile,1); close(opfile); }


			for(j=0;j<countpipe;j++)
			{
			close(pipes[j][0]);
	  		close(pipes[j][1]);
	  		}
	  		


	  		//printf("countfl:%d\n",countfl );
	  		searchenv(argv,countfl);

	  		if(!strcmp(argv[0],"cd")){	// do nothing
	  								 //printf("%d",runinternal(argv[0],argv));	
	  									}
	
	  		else if(!strcmp(argv[0],"history")) {  showhistory();	}
	  		else
	  		{
	  		//f
	  			//printf("%s  %s\n",*argv,*(argv+1) );
	  			
			execvp(*argv,argv);
			}

			exit(0);

		}
		else
		{


			if(!strcmp(argv[0],"cd"))
	  		{
	  			searchenv(argv,countfl);
	  			//printf("reached here:%s\n",argv[1]);
	  			if(runinternal(argv[0],argv)==-1)
	  				perror(NULL);
	  			
	  		}
			

	  		//free(argv);

		}
	}

	 
	 	for(j=0;j<countpipe;j++)
			{
			close(pipes[j][0]);
	  		close(pipes[j][1]);
	  		}

	  	for(i=0;i<countpipe;i++){wait(&x);}

	  	free(argvp)	;


}