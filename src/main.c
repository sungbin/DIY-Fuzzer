#include <stdio.h>
#include <string.h>

#include "../include/runner.h"

int 
main(int argc, char* argv[])
{

	if(argc < 3) {
                printf("ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN TWO!\n");
                return 1;
        }

	// argv[1]: target_path;
	// argv[2]: input_path;
	
	if(! runner(argv[1],argv[2])) {
		/*  Pass: return 0 */
		//printf("INPUT: %s - Pass\n", in_str); // TODO: multiple arguments

	} else {
		/*  Fail  */
		//printf("INPUT: %s - Fail\n", in_str); // TODO: multiple arguments
	}

	return 0;
}

