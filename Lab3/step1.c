/* 
 * * Name: Frankie Fazlollahi 
 * * Date: 1/20/2022
 * * Title: Lab3 - Part 1
 * * Description: TCP server that accepts a client connection for file transfer. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

//Declare socket file descriptor.
int sockfd, connfd, rb, sin_size;

//Declare receiving and sending buffers of size 10 bytes
char buf[1024];

//Declare server address to which to bind for receiving messages and client address to fill in sending address
struct sockaddr_in servAddr, clienAddr;

//Connection handler for servicing client request for file transfer
void* connectionHandler(void* sock){
   	//declare buffer holding the name of the file from client
    	char buff[20];
    	//get the connection descriptor
    	int sockNum = *(int *) sock;
    	int n;
    	FILE *fp;
   	//Connection established, server begins to read and write to the connecting client
   	printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
   
	//receive name of the file from the client
	if((n = read(connfd, buff, sizeof(buff))) > 0){
        	printf("opening file %s\n", buff);
    	}
   	//open file and send to client
   	fp = fopen(buff, "r");
   	if(fp != NULL){
       		printf("Opened file sucessfully\n");
   	}
	int x;
   	while(x = fread(&buf, sizeof(char), 10, fp)){
       		write(sockNum, buf, x);
   	}
   	//read file and send to connection descriptor
   	printf("File transfer complete\n");
   
   	//close file
   	fclose(fp);
    
   	//Close connection descriptor
   	close(connfd);

   	return 0;
}


int main(int argc, char *argv[]){
 	//Get from the command line, server IP, src and dst files.
 	if (argc != 2){
		printf ("Usage: %s <port #> \n",argv[0]);
		exit(0);
 	} 
 	//Open a TCP socket, if successful, returns a descriptor
 	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
     		perror("Failure to setup an endpoint socket");
     		exit(1);
 	}
 	//Setup the server address to bind using socket addressing structure
 	servAddr.sin_family = AF_INET;
 	servAddr.sin_port = htons(atoi(argv[1]));
 	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	//bind IP address and port for server endpoint socket 
 	if((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
     		perror("Failure to bind server address to the endpoint socket");
     		exit(1);
 	}
 	// Server listening to the socket endpoint, and can queue 5 client requests
 	printf("Server listening/waiting for client at port 5000\n");
 	listen(sockfd, 5);
 	sin_size = sizeof(struct sockaddr_in);

 	//Server accepts the connection and call the connection handler
 	connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size);
 	connectionHandler((void*)&connfd);

 
 	//close socket descriptor
 	close(sockfd);

 	return 0;
}

