#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Executes the command "cat fixtures | grep <search_term> | cut -b 1-9".
 *
 * When run the program give a word that you need to take the pattern
 * 
 * Example
 *      1. compile --> gcc exercise3.2.c_skel.c -o ex 	
 * 	2. run     --> ./ex 'New Zealand' 	  
 */


#define INPUTFILE "fixtures"

void die(const char *msg);

int main(int argc, char **argv)
{
	int status;
	int i;

	// arguments for commands
	char *cat_args[] = {"cat", INPUTFILE, NULL};
	char *grep_args[] = {"grep", "-i", argv[1], NULL};
	char *cut_args[] = {"cut", "-b", "1-9", NULL};

	if (argc < 2)
	{
		printf("%s: missing operand\n", argv[0]);
		printf("Usage: %s <search_term in %s>\n", argv[0],INPUTFILE);
		exit(EXIT_FAILURE);
	}
	

	// make 2 pipes (cat to grep and grep to cut); each has 2 fds
	int pipes[4];
      
      	// sets up 1st pipe
      	int pipe_cat_grep[2] = {pipes[0], pipes[1]};
      
      	if(pipe(pipe_cat_grep) == -1)
		die("cat_grep_pipe");
	
	// sets up 2nd pipe
      	int pipe_grep_cut[2] = {pipes[2], pipes[3]};
      	
	if(pipe(pipe_grep_cut) == -1)
		die("grep_cut_pipe");
	
	// we now have 4 fds:
	// pipes[0] = read end of cat->grep pipe (read by grep)
	// pipes[1] = write end of cat->grep pipe (written by cat)
	// pipes[2] = read end of grep->cut pipe (read by cut)+
	// pipes[3] = write end of grep->cut pipe (written by grep)

	// fork the first child (to execute cat)

	if (fork() == 0)
	{
		// replace cat's stdout with write part of 1st pipe
		close(1); 						
	  
		if(dup(pipe_cat_grep[1]) == -1)  
			die("dup()");
   
		// close all pipes (very important!); end we're using was safely copied
		close(pipe_cat_grep[0]);       
		close(pipe_grep_cut[0]);
		close(pipe_grep_cut[1]); 
		// Execute the cat command
		
		if(execvp("cat", cat_args) == -1)
			die("execvp()");

		//exit(EXIT_SUCCESS);
	}
	else
	{
		// fork second child (to execute grep)
		if (fork() == 0)
		{
			// replace grep's stdin with read end of 1st pipe
			
            close(0);
            close(1);
             
            if(dup2(pipe_cat_grep[0], 0) == -1)
					die("dup()");
			// replace grep's stdout with write end of 2nd pipe
			
			if(dup2(pipe_grep_cut[1], 1) == -1)
					die("dup()");

			// close all ends of pipes
			
            close(pipe_cat_grep[1]);
            close(pipe_grep_cut[0]);
            
			// execute grep command
			
			if(execvp("grep", grep_args) == -1)
					die("execvp()");

			exit(EXIT_SUCCESS);
		}
		else
		{
			// fork third child (to execute cut)
			if (fork() == 0)
			{
				// replace cut's stdin with input read of 2nd pipe
				
				close(0);
				if(dup(pipe_grep_cut[0]) == -1)
						die("dup()");

				// close all ends of pipes
				
				close(pipe_cat_grep[0]);
				close(pipe_cat_grep[1]);
				close(pipe_grep_cut[1]);

				// execute cut command
				
				if(execvp("cut", cut_args) == -1)
						die("execvp");
						
				exit(EXIT_SUCCESS);		
			}
		}
	}

	// only the parent gets here and waits for 3 children to finish
	// It's a good idea to close all your pipes (the parent needs none!)
	// before waiting for your children! 

    close(pipe_cat_grep[0]);
    close(pipe_cat_grep[1]);
    close(pipe_grep_cut[1]);
    close(pipe_grep_cut[0]);
     
    wait(&status);
}


/* A better way to Die (exit) */
void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

