// Name: Frankie Fazlollahi
// Date: 01-06-2022
// COEN146L : Lab 1 - Step1
// Description: Copying data from one file to another using function calls

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048 // buffer size

//cat /dev/random | head -c 100000 > src.dat

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	FILE *src, *dst;
	void* buf;
	
	src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}
	
	// allocate a buffer to store read data
	buf = malloc((size_t)BUF_SIZE);

   	int bytes_read;
    	// reads content of file is loop iterations until end of file
	while((bytes_read = fread(buf, 1, BUF_SIZE, src)) > 0)
	{
        	// writes bytes_read to dst_filename
		if(fwrite(buf, 1, bytes_read, dst) < 0)
		{
			fprintf(stderr, "write error: %i\n", errno);
			exit(0);
        	}
    	}
	// closes src file pointer
	fclose(src);
	// closes dst file pointer
	fclose(dst);
	// frees memory used for buf
	free(buf);
	
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}
	// get the source and destination files from the command line arguments
	char* src_filename = argv[1];
	char* dst_filename = argv[2];
	
    	printf("Copying %s to %s\n", src_filename, dst_filename);
    	func_copy(src_filename, dst_filename);
	return 0;
}
