#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int filedescriptor_1;
	int filedescriptor_2;
	int filedescriptor_3;
	
	filedescriptor_1=open("my.txt", O_CREAT | O_TRUNC , S_IRWXU);
	
	if(filedescriptor_1<0)
	{
		printf("Error opening or creating 'my.txt'\n");
		if(errno==EACCES)
		{
			printf("Error #%d (EACCES) : Permission denied.\n" , EACCES);
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		printf("'my.txt' was created or opened");
		printf(" and it has the file descriptor %d \n" , filedescriptor_1);
	}
	
	//use the fcntl() function to copy the file descriptor
	if((filedescriptor_2=fcntl(filedescriptor_1,F_DUPFD,0))<0)
	{
		printf("Error duplicating the file descriptor. \n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file descriptor duplicated...");
		printf(" The new file descriptor is  %d \n" , filedescriptor_2);
	}
	
	//use the fcntl() function to duplicate the file descriptor , but set it to a higher number as with the third parameter which is the minimum it can take
	if((filedescriptor_3=fcntl(filedescriptor_1,F_DUPFD,11))<0)
	{
		printf("Error duplicating the file descriptor.");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(" The file descriptor duplicated again...");
		printf("The new file descriptor is  %d.\n" , filedescriptor_3);
	}
	
	close(filedescriptor_1);
	close(filedescriptor_2);
	close(filedescriptor_3);
		
	
	return 0;
}
