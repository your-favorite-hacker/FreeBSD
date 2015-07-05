/* yes, this code will segfault if you dont give it an argument */
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>

void help(){
	printf("rainroot caller\nuse appropiate syscallnumber (default: 210)\nexample: ./caller 210\n\nby dash\n");
	

}

int main(int argc, char *argv[]){

	int scall=-1;
	if(argc<2){
		help();
		exit(1);
	}
	
	scall = atoi(argv[1]);

	syscall(scall);

	return(0);
}
