#include"program.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int pipeStatus, pipefd[2];
	
	pipeStatus = pipe(pipefd);
	if(pipeStatus != 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	if(fork() == 0)
	{
		char sendString[BUF_SIZE];
		
		if(close(pipefd[0]) == -1)	// close unused pipe end
		{
			perror("Child:close pipefd[0]");
		}
		
		printf("Enter the data to be sent to parent: ");
		fgets(sendString,sizeof(sendString),stdin);
		
		if(write(pipefd[1],sendString,strlen(sendString)) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		
		if(close(pipefd[1]) == -1)
		{
			perror("Child:close pipefd[1]");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char receiveString;
		int turn,numBytes; 
		
		if(close(pipefd[1]) == -1)	// close unused pipe end
		{
			perror("Parent:close pipefd[1]");
		}
		
		while(read(pipefd[0],&receiveString,1) > 0)
			write(STDOUT_FILENO, &receiveString,1);
		
		write(STDOUT_FILENO,"\n",1);
		
		if(close(pipefd[0]) == -1)
		{
			perror("Parent:close pipefd[0]");
			exit(EXIT_FAILURE);
		}
	}	
		
	return 0;
}

