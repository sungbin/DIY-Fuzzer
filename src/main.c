#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/runner.h"

int 
main (int argc, char* argv[])
{

	if (argc < 4) {
                fprintf(stderr, "ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN THREE!\n");
                exit(1);
        }
	if (access(argv[1], X_OK) == -1) {
                fprintf(stderr, "ERROR: CANNOT EXECUTE %s\n",argv[1]);
                exit(1);
	}
	if (access(argv[2], R_OK) == -1) {
                fprintf(stderr, "ERROR: CANNOT READ %s\n",argv[1]);
                exit(1);
	}

	// argv[1]: target_path;
	// argv[2]: input_path;
	// argv[3]: output_path;
	
	runner_error_code error_code = runner(argv[1], argv[2], argv[3]);

	printf("0x%x %d\n", error_code.type, error_code.exit_code);

	return 0;
}

