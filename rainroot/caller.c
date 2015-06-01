/* yes, this code will segfault if you dont give it an argument */
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int scall=-1;
	scall = atoi(argv[1]);

	syscall(scall);

	return(0);
}
