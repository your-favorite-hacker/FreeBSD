/* caller c tool
   if you do not have a compiler, use perl:
   perl -e 'syscall(211);'
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

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
