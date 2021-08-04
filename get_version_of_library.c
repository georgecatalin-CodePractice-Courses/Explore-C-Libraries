#include <stdio.h>
#include <jpeglib.h>

int main(int argc, char **argv)
{
	printf("The version of the jpeg library installed on this computer is %d. \n", JPEG_LIB_VERSION);
	return 0;
}
