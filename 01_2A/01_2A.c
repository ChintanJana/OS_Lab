/*
TEAM NUMBER - 1
MEMBERS -
ANANYA BHOWMICK       002111001016
ARIJIT SAHA           002111001118
ROHEENA PAL           002111001096
CHINTAN JANA          002111001115
*/

/*
ASSIGNMENT DETAILS -
ASSIGNMENT NUMBER 2A
Program for using signal system call
*/

/*
COMPILATION COMMAND -
gcc -o Team1_2A Team1_2A.c
./Team1_2A
*/

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int signal){
    if(signal == SIGINT){ /* When SIGINT is caught, the message is printed*/
        printf("Ha Ha, Not Stopping\n");
	}
}

int main(){
    if(signal(SIGINT, signalHandler) == SIG_ERR){
        perror("Error occured in catching SIGINT.\n");
    }

    while(1){ /* Running an infinite loop to demonstrate the interrupt*/
        printf("Team 1 process running\n");
        sleep(1);
    }

    return 0;
}
