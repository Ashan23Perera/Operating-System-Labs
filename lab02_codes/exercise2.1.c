/*
 *  	program where the parent reads a string from the user and send it to the child
 *	and the child capitalizes each letter and sends back the string to parent and parent	 
 *	displays it. You'll need twpipes to communicate both ways 
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
	pid_t pid;
	int status;
	int pipe_ends_1[2]; //FIRST PIPE
	int pipe_ends_2[2]; //SECOND PIPE
    	char user[100]; 


	//zeroth element - read end
	//first element  - write end 
	
	//CREATE TWO PIPES
	if(pipe(pipe_ends_1) &&  pipe(pipe_ends_2))
	{
		perror("Create pipe");
		return -1;
	}
	
	//CREATE A CHILD PROCESS
	pid = fork();
	if(pid < 0){
		perror("Error fork");
		return -1;
	}

	// parent 
	if(pid > 0){
//READ		
		char user[128];
	    	char buff[128];

		//CLOSE THE READ END OF FIRST PIPE
		close(pipe_ends_1[0]);

		//TAKE A SIMPLE WORD		
		printf("Simple Word: ");
		fgets(user, sizeof(user), stdin);

		//WRITE TO WRITE END OF THE FIRST PIPE
		write(pipe_ends_1[1],user,sizeof(user));

		//CLOSE THE WRITE END OF FIRST PIPE
		close(pipe_ends_1[1]);
//====================================================================	    
	    	sleep(2);
//WRITE	    
		//CLOSE THE WRITE END OF SECOND PIPE
		close(pipe_ends_2[1]);

		//READ THE READ END OF THE SECND PIPE (OUTPUT - CAPITAL WORD)
		read(pipe_ends_2[0], buff, 128);
		printf("%s\n",buff);
	}

	// child 
	if(pid == 0){
		char buff[128];

//READ
		//CLOSE THE WRITE END OF FIRST PIPE
		close(pipe_ends_1[1]);

		//READ THE READ END OF FIRST PIPE (take the simple word from parent)
		int count = read(pipe_ends_1[0], buff, 128);

		buff[count] = '\0';

		//CONVERT SIMPLE WORD TO CAPITAL
		int i;
		for(i = 0; i < (strlen(buff));i++)
		{
				buff[i] = buff[i] - 32;
		}	
//=================================================================

//WRITE
		//CLOSE THE READ END OF SECOND PIPE
		close(pipe_ends_2[0]);
	
		//WRITE TO WRITE END OF THE SECOND PIPE (write cacpital word)
		write(pipe_ends_2[1],buff,strlen(buff));

		//CLOSE WRITE END OF SECOND PIPE
		close(pipe_ends_2[1]);	
	}    

	return 0;
}
