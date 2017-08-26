#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

int main()
{
    int fd, fd2;
	
	char* fifo  = "/tmp/fifo";
	char* fifo2 = "/tmp/fifo2";
	
	char buf[MAX_SIZE];
	char* trargs[] = {"tr", "[:lower:]", "[:upper:]", NULL};
	
	//create two named pipes
	mkfifo(fifo,0666);
	mkfifo(fifo2,0666);
	
	//replace standard input in to fd
	fd = open(fifo, O_RDONLY);
	dup2(fd, 0);
	
	//replace standard input in to fd2
	fd2 = open(fifo2, O_WRONLY);
	dup2(fd2, 1);
	
	//execute tr command
	execvp("tr", trargs);
	
	close(fd);
	close(fd2);
	
 return 0;	
}
