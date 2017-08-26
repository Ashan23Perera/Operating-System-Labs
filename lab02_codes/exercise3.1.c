/*
*   program that uses fork() and exec() to create a process of ls and get the result of ls
*   back to the parent process and print it from the parent using pipes
*   
*
*
*	The implementaion have use dup 
*
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
	pid_t pid;
	int pipe_ends[2]; 
	char * ls[] ={"ls", NULL};

	//create a pipe
	if(pipe(pipe_ends)) 
	{
		perror("Pipe creation");
		return -1;
	}
	
	//create child process
	pid = fork();
	if(pid < 0) 
	{
		perror("Fork");
		return -1;
	}
	
	/* parent */
	if(pid == 0) 
	{ 
		//replace the std out in pipe end write
		dup2(pipe_ends[WRITE_END], 1);
		
		//close read end of pipe
		close(pipe_ends[READ_END]);
		
		//execute ls command (It will give the current directory files)
		execvp("ls", ls);
		
		sleep(1);
		exit(EXIT_SUCCESS);
	}
	/* child */
	if(pid > 0) 
	{
		 
		char buff[1000];
		
		//close the write end of pipe
		close(pipe_ends[WRITE_END]);
		
		//read the read end
		int count = read(pipe_ends[READ_END], buff, 1000);
		
		//write to STDOUT
		write(1, &buff, count);
		
		
	}
	return 0;
}
