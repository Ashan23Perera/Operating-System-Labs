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
	
	char user[MAX_SIZE];
	char buf[MAX_SIZE];
	
	//create two named pipes
	mkfifo(fifo,0666);
	mkfifo(fifo2,0666);
	
	
	//take a simple word user input
	fgets(user, sizeof(user), stdin);
	fd = open(fifo, O_WRONLY);
	write(fd, user, strlen(user));
	close(fd);
	
	//read and write capital word
	fd2 = open(fifo2, O_RDONLY);
	read(fd2, buf, MAX_SIZE);
	printf("Capital Word: %s\n", buf);
	
	close(fd2);
	
	unlink(fifo);
	unlink(fifo2);
	
 return 0;	
}
