#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char* argv[])
{

        char buf[1024];
        fgets(buf, 1024, stdin);
        buf[strlen(buf) - 1] = '\0';

	if(atoi(buf) < 1) {
		printf("non-positive \n");
		exit(1);
	} else {
		printf("positive \n");
	}

	return 0;
}
