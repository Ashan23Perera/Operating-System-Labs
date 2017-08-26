/*
*  program called mycopy using open() , read() , write() and close() which takes two
*  arguments, viz. source and target file names, and copy the content of the source file into the
*  target file. If the target file exists, just overwrite the file
*
* source file - fixtures
* target file - target
*
*/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define SOURCEFILE "fixtures"
#define TARGETFILE "target"

int main()
{
	
	int out_1, out_2;
	size_t ret;
	char* banner = "String to write and read";
	size_t size = strlen(banner);
    	char* buffer = malloc(size + 1); 
	  
	printf("======Open source file to read and target file to write====\n");
        
        //OPEN SOURCE FILE(fixtures) FOR READ ONLY
	out_1 = open(SOURCEFILE, O_RDONLY);

	//OPEN TARGET FILE(target0) FOR WRITE AND APPEND 
	out_2 = open(TARGETFILE, O_WRONLY | O_APPEND);
	if(out_1 == -1 && out_2 == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	} 
 	
	//READ THE FILE AND WRITE THE FILE
	while(1)
	{
		//READ
		ret = read(out_1,buffer,size);
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

		//WRITE
		ret = write(out_2,buffer,size);
		if(ret == -1)
		{
			fprintf(stderr,"Error writing to file\n");
			return 1;
		}
	
	}
	
	printf("\n=====Done with reading and writing. Closing the file===\n");
	
	free(buffer);
	if(close(out_1)== -1 && close(out_2))
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

     return 0;
}
