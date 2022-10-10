// Name: Frankie Fazlollahi
// Date: 01-06-2022
// COEN146L : Lab 1 - Step3
// Description: Measuring time to copy data from one file to another using function and system calls

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048 //buffer size

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

	buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data

    	int bytes_read;
    	while((bytes_read= fread(buf, 1, BUF_SIZE, src)) > 0){  // reads content of file is loop iterations until end of file
        	if(fwrite(buf, 1, bytes_read, dst) < 0){   // writes bytes_read to dst_filename 
			fprintf(stderr, "write error: %i\n", errno);
            		exit(0);
        	}
    	}

    	fclose(src);    // closes src file pointer
    	fclose(dst);    // closes dst file pointer
    	free(buf);      // frees memory used for buf
	
	return 0;
}

// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char* src_filename, char* dst_filename)  {
    	int src_fd, dst_fd;
	void* buf;
	
	src_fd = open(src_filename, O_RDONLY);	// opens a file for reading
	if (src_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		close(src_fd);
		exit(0);
	}
	// O_WRONLY - write only
	// O_CREAT - create file if it doesn't exist
	// O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
	// opens a file for writing; erases old file/creates a new file
	dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC);	
	if (dst_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		close(dst_fd);
		exit(0);
	}


	// read/ write loop
	buf = malloc((size_t)BUF_SIZE);   // allocate a buffer to store read data

	int bytes_read;
	while((bytes_read = read(src_fd, buf, BUF_SIZE)) > 0){	// reads up to BUF_SIZE bytes from src_filename
		if(write(dst_fd, buf, bytes_read) < 0){	// writes bytes_read to dst_filename
			fprintf(stderr, "write error: %i\n", errno);
			exit(0);
		}
	}
	
	close(src_fd);	// closes src_fd file descriptor
	close(dst_fd);	// closes dst_fd file descriptor
	free(buf);	// frees memory used for buf
	
	return 0;
}

// checks the runtime to copy a file using functions vs system calls
void check_copy_times(char* src_filename, char* dst_filename) {
	clock_t func_start, func_end, syscall_start, syscall_end;
	double func_time, syscall_time;

	// capture runtime of func_copy by using clock before and after func_copy is called
	func_start = clock();
    	func_copy(src_filename, dst_filename);
    	func_end = clock();

    	func_time = ((double) (func_end - func_start)) / CLOCKS_PER_SEC;

	// capture runtime of syscall_copy by using clock before and after syscall_copy is called
	syscall_start = clock();
    	syscall_copy(src_filename, dst_filename);
    	syscall_end = clock();
	
    	syscall_time = ((double) (syscall_end - syscall_start)) / CLOCKS_PER_SEC;

	printf("Time to copy using functions: %.7f\n", func_time);
	printf("Time to copy using syscalls: %.7f\n", syscall_time);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}

	char* src_filename = argv[1];   //get the source and destination files from the command line arguments
    	char* dst_filename = argv[2];
	
    	check_copy_times(src_filename, dst_filename);

	return 0;
}
