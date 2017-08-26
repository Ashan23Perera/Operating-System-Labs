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

int  pid;
int i;
for(i = 0; i< 3;i++){
	pid  =  fork();

if (pid  <  0){
	perror("fork");
	exit(1);
}

if (pid  ==  0){
	puts("This  is the  child  process");
}
else{
	wait(NULL); 
	puts("This  is the  parent  process");
}  

}

return  0;

}