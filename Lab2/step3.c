/* 
 * * Name: Frankie Fazlollahi
 * * Date: 1/13/2022
 * * Title: Lab1 – task 3 
 * * Description: Calculates time elapsed for various tasks when we need to use a DNS lookup
 * */


#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc != 2){ // check usage
		fprintf(stderr, "usage: %s <n parallel connections \n", argv[0]);
		exit(1);
	}
	int n = atoi(argv[1]); // n parallel connections
	int RTT0 = 3;
	int RTT1 = 20;
	int RTT2 = 26;
	int RTTHTTP = 47;
	int RTTDNS = RTT0 + RTT1 + RTT2;

	printf("One object: %d msec\n", RTTDNS + 2 * RTTHTTP);
	printf("Non-persistent 6 objects: %d msec\n", RTTDNS + 2 * RTTHTTP + 2 * 6 * RTTHTTP);

	int np = (n > 6)? 1: 6/n;
	if ( (n < 6) && (6 % n != 0))
		np += 1;

	printf("%d parallel connection - Persistent: %d msec\n", n, RTTDNS + 2 * RTTHTTP + np * RTTHTTP);
	printf("%d parallel connection - Non-Persistent: %d msec\n", n, RTTDNS + 2 * RTTHTTP + 2 * np * RTTHTTP);

	return 0;
}
