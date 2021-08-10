#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void read_flags(int file_descriptor)
{
	int return_value;
	
	if((return_value=fcntl(file_descriptor,F_GETFL,0))<0)
	{
		printf("Error opening file descriptor.");
		return;
	}
	
	printf("The access mode for the file descriptor %d.\n",file_descriptor);
	
	switch(return_value & O_ACCMODE)
	{
		case O_RDONLY:
		printf("Read only..");
		break;
		case O_WRONLY:
		printf("Write only...");
		break;
		case O_RDWR:
		printf("Read and write...");
		break;
		default:
		printf("Do not know");
	}
	
	if(return_value & O_APPEND)
	{
		printf("+Append");
	}
	
	if(return_value & O_NONBLOCK)
	{
		printf("+Nonblocking");
	}
	
	printf("\n");
}

int main()
{
	int fd1,fd2;
	
	if((fd1=open("append.txt", O_CREAT | O_APPEND, S_IRWXU))<0)
	{
		printf("Error when opening/creating 'append.txt'");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File 'append.txt' opened successfully with this file descriptor %d.\n", fd1);
	}
	
	if((fd2=open("nonblocking.txt", O_CREAT | O_NONBLOCK, S_IRWXU))<0)
	{
		printf("Error when opening or creating 'nonblocking.txt' ");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File 'nonblocking.txt' was opened successfully with the file descriptor %d \n", fd2);
	}
	
	read_flags(fd1);
	read_flags(fd2);
	
	if(close(fd1)<0)
	{
		printf("Error when closing fd1\n");
		exit(EXIT_FAILURE);
	}
	
	if(close(fd2)<0)
	{
		printf("Error when closing fd2\n");
		exit(EXIT_FAILURE);
	}
	
	
	
	return 0;
}
