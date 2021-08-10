#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
		puts("The fnctl() function can have multiple uses:");
		printf("Duplicate an existing file descriptor (F_DUPFD) %d \n", F_DUPFD);
		printf("Get file descriptor flags (F_GETFD) %d \n" , F_GETFD);
		printf("Set file descriptor flags (F_SETFD) %d \n" , F_SETFD);
		printf("Get file status flags (F_GETFL) %d \n", F_GETFL);
		printf("Set file status flags (F_SETFL) %d \n", F_SETFL);
		printf("Get record locks (F_GETLK) %d \n" , F_GETLK);
		printf("Set record locks (F_SETLK) %d \n", F_SETLK);
		printf("Get asynchronous I/O ownership (F_GETOWN) %d \n" , F_GETOWN);
		printf("Set asynchronous I/O ownership (F_SETOWN) %d \n" , F_SETOWN);
	
		return 0;
}
