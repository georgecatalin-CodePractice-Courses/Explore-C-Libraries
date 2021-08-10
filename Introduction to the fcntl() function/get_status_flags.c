// status flags it is about the O_RDONLY, O_WRONLY, O_RDWR which are used in the open() function


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int file_status_flags;
	int rVal;
	int filedescriptor;
	
	if((filedescriptor=open("my.txt", O_CREAT | O_APPEND, S_IRWXU))<0)
	{
		printf("Error opening file");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File was opened\n");
	}
	
	if((rVal=fcntl(filedescriptor,F_GETFL))<0)
	{
		printf("Error when getting file status flags");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File status flags retrieved successfully.\n");
	}
	
	file_status_flags=rVal & O_ACCMODE;
	
	if(file_status_flags==O_RDONLY)
	{
		printf("File is in read only\n");
	}
	else if(file_status_flags==O_WRONLY)
	{
		printf("File is in write only\n");
	}
	else if(file_status_flags==O_RDWR)
	{
		printf("File is in read/write .\n");
	}
	else
	{
		printf("Can not tell you.");
	}
	
	
	if (close(filedescriptor)<0)
	{
		printf("Error when closing file descriptor");
	}
	else
	{
		printf("File descriptor closed successfully.\n");
	}
	
	
	return 0;
}
