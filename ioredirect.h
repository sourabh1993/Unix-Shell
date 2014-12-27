void ioredirections(char **arg,int *in,int *out)
{
	int fd1;
	char fname[50];
	int len,i,ind=0,j;
	char arr[200];

	len=strlen(*arg);

	for(i=0;i<len;)
	{
		switch((*arg)[i])
		{
			case '>':

						i++;
						j=0;
						int dq=0,sq=0;
						int getout=0;
						int doubleredir=0;

						if((*arg)[i]=='>') { doubleredir=1; i++;}
						
						//for(j=0;	(*arg)[i]!=' ' && (*arg)[i]!='\0' && (*arg)[i]!='>' && (*arg)[i]!='<'	;	i++ )

						while(1)
						{
							switch((*arg)[i])
							{
								case '"':  if(sq==1)fname[j++]=(*arg)[i++];
										   else if(dq==0){i++;dq=1;}
										   else if(dq==1){ i++;dq=0;}	
									   	   break;

								case '\'': if(dq==1)fname[j++]=(*arg)[i++];
										   else if(sq==0){i++;sq=1;}
										   else if(sq==1){ i++;sq=0;}	
									   	   break;

								case ' ': if(dq || sq) fname[j++]=(*arg)[i++];
										  else if(j!=0) { fname[j]='\0'; getout=1;}
										  else i++;
										  break;	

								case '<':
								case '>': if(dq || sq) fname[j++]=(*arg)[i++];
										  else { fname[j]='\0'; getout=1;}
										  break;

								case '\0': getout=1;
										   break;			  

								default	: fname[j++]=(*arg)[i++];
										  break;

							}

							if(getout)break;
							

						}

						fname[j]='\0';

						if(*out!=-1)close(*out);

						if(doubleredir)fd1=open(fname,O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
							 else fd1=open(fname,O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
						 		 //empty a  write(fd1," ",2);

						*out=fd1;
						break;



			case '<':	
						i++;
						j=0;
						dq=0;sq=0;
						getout=0;
						doubleredir=0;

						if((*arg)[i+1]=='<') { doubleredir=1; i++;}
						
						//for(j=0;	(*arg)[i]!=' ' && (*arg)[i]!='\0' && (*arg)[i]!='>' && (*arg)[i]!='<'	;	i++ )

						while(1)
						{
							switch((*arg)[i])
							{
								case '"':  if(sq==1)fname[j++]=(*arg)[i++];
										   else if(dq==0){i++;dq=1;}
										   else if(dq==1){ i++;dq=0;}	
									   	   break;

								case '\'': if(dq==1)fname[j++]=(*arg)[i++];
										   else if(sq==0){i++;sq=1;}
										   else if(sq==1){ i++;sq=0;}	
									   	   break;

								case ' ': if(dq || sq) fname[j++]=(*arg)[i++];
										  else { fname[j]='\0'; getout=1;}
										  break;	

								case '<':
								case '>': if(dq || sq) fname[j++]=(*arg)[i++];
										  else { fname[j]='\0'; getout=1;}
										  break;

								case '\0': getout=1;
										   break;			  

								default	: fname[j++]=(*arg)[i++];
										  break;

							}

							if(getout)break;


						}

						fname[j]='\0';

						if(*in!=-1)close(*in);

						
						fd1=open(fname,O_RDONLY);

						*in=fd1;
			
						break;			// Break from outer switch



			default:
										
					arr[ind++]=(*arg)[i++];
					break;
		}


	}

	arr[ind]='\0';

	strcpy(*arg,arr);

}