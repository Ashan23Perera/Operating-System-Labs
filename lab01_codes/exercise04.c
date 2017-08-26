#include <stdio.h>  
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int  main(void)
{

int pid, i = 0;
char str1[100], str2[100];

	while(1){

    	pid = fork();
    	if (pid  <  0){
			perror("fork");
			exit(1);
		}

		if (pid  ==  0){
			//Enter the command
			printf("Command $ ");
   			scanf("%s", str1);
        	//Enter the path
			printf("Argument $ ");
   			scanf("%s", str2);

			execl(str1,  "-l",  str2,  NULL); //"/bin/ls"
		}else{
			wait(NULL); 
		}   
    	i = i + 1;	
	}
	free(str1);
	free(str2);
	return  0;
}