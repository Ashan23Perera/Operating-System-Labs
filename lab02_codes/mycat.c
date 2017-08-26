/*
* 
* Exercise 1.2 -- part a 
* reads a text file and writes the output to the standard output
* here read the fixtures file
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define INPUTFILE "fixtures"

int main()
{
	int out;
	size_t ret;
	char* banner = "String to write and read";
	size_t size = strlen(banner);

	printf("======Opening the file to read the string written====\n\n");
        
        //OPEN read.txt FILE  
	out = open(INPUTFILE, O_RDONLY);
	if(out == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	} 

	// size of a char is 1. This buffer holds the read back value. 
	char* buffer = malloc(size+1); 
        
        //READ THE FILE AND WRITE TO STANDARD OUTPUT
	while(1)
	{
		//READ THE FILE 
		ret = read(out,buffer,size);
		if(ret == -1)
		{
			fprintf(stderr,"Error reading from file\n");
			return 1;
		}
		if(ret == 0)
		{
		     break;
		}
		// we have to null terminate the string ourselves. 
		buffer[ret] = '\0';  
		printf("%s",buffer);
	}
	
	printf("\n=====Done with reading. Closing the file===\n");
	
	free(buffer);
	ret = close(out);
	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}


   return 0;
}
