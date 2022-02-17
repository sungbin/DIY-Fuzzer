#include <stdio.h>
#include <string.h>

#include "../include/runner.h"

int 
main (int argc, char* argv[])
{

	if (argc < 4) {
                printf("ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN THREE!\n");
                return 1;
        }

	// argv[1]: target_path;
	// argv[2]: input_path;
	// argv[3]: output_path;
	
	if (! runner(argv[1], argv[2], argv[3])) {
		/*  Pass: return 0 */
//		printf("  - Pass  \n"); // TODO: print result!

	}
	else {
		/*  Fail  */
//		printf("  - Fail  \n"); // TODO: print result!
	}

	return 0;
}

