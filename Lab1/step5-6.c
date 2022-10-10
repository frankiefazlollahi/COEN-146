// Name: Frankie Fazlollahi
// Date: 01-06-2022
// COEN146L : Lab 1 - Steps 5 & 6
// Description: Calculating number of circuit switching user and packet switching probabilities
#include <stdio.h>  
#include <math.h>
#include <stdlib.h>


double factorial(double n)
{
	int i;
    	double fact = 1;
    	for(i = n; i > 1; --i){
        	fact *= i;
    	}
    	return fact;
}

int main(int argc, char *argv[]) {
	if (argc !=5){
		fprintf(stderr,"usage: ./a.out <linkBandwidth> <userBandwidth> <tPSusers> <nPSusers> \n");
		exit(0);
    	} 
   	int i, linkBandwidth, userBandwidth, nCSusers, nPSusers;
   	double pPSusers, tPSusers, pPSusersBusy, pPSusersNotBusy;
   
   	// Get values from command line
   	linkBandwidth = atoi(argv[1]);  // bandwidth of network link
   	userBandwidth = atoi(argv[2]);  // user bandwidth
   	tPSusers  = atof(argv[3]);      // percentage of time a packet switching user needs to transmit
   	nPSusers = atoi(argv[4]);       // number of packet switching users

   	// 5a: Circuit Switching Senario
   	nCSusers = linkBandwidth/userBandwidth;  // how many users --> nCSusers
   	printf("5a: Circuit switching senario: %d users\n", nCSusers);
   
   	// 6: Packet Switching Senario
   	// compute: 6a, b, c, d, e, f, g, h 
   	pPSusers = tPSusers; //6a
   	pPSusersNotBusy = 1 - pPSusers;  //6b
   	double pAllNotBusy = pow(pPSusersNotBusy, (nPSusers-1)); //6c
   	double pOneBusy = pPSusers * pow(pPSusersNotBusy, (nPSusers-1)); //6d
   	double pExactlyOne = nPSusers * (pPSusers * pow(pPSusersNotBusy, (nPSusers-1))); //6e
   	double pTenBusy = pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers-10));   //6f
   	double coefficient = factorial(nPSusers)/(factorial(10)*factorial(nPSusers-10)); ////6g
   	double pAnyTenBusy = coefficient * pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers-10));

   	i = 11;      //6h
   	double pTenMoreBusy = 0;
   	for(i; i <= nPSusers; ++i){
       		double coefficient = factorial(nPSusers)/(factorial(i)*factorial(nPSusers-i));
       		pTenMoreBusy += coefficient * pow(pPSusers, i) * pow(pPSusersNotBusy, (nPSusers-i));
   	}
   
   
   	printf("6: Packet switching senario");
   	printf("6a: The probability that a given (specific) user is busy transmitting = %f\n", pPSusers);
   	printf("6b: The probability that ine specific other user is not busy =  %f\n", pPSusersNotBusy);
   	printf("6c: The probablility that all of the other specific other users are not busy =  %e\n", pAllNotBusy);
   	printf("6d: The probability that one specific user is transmitting and the remianing users are not transmitting =  %e\n", pOneBusy);
   	printf("6e: The probability that exactly one of the nPSusers users is busy is pPSusers times the probability that a given specific user is transmitting and the remaining users are not transmitting = %le\n", pExactlyOne);
   	printf("6f: The probabalitiy that 10 specific users of nPSusers are transmitting and the others are idle = %lg\n", pTenBusy);
   	printf("6g: The probability that any 10 users of nPSusers are transmitting and the others are idle = %lg\n", pAnyTenBusy);
   	printf("6h: The probability that more than 10 users of nPSusers are transmitting and the others are idle = %lg\n", pTenMoreBusy);
   	return 0;
}
