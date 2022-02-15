#include <stdio.h>

#include "../include/runner.h"

int 
main(int argc, char* argv[])
{

	if(argc < 2) {
                printf("ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN ONE!\n");
                return 1;
        }

	return runner(argc-1, (argv+1) ); // Excuatable-Binary-File-Name, Text-Input
}
