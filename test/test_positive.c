#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char* argv[])
{

	if(atoi(argv[1]) < 1) {
		printf("non-positive \n");
		exit(1);
	} else {
		printf("positive \n");
	}

	return 0;
}
