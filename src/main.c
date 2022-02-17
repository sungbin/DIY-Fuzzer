#include <stdio.h>

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
	
	runner_error_code error_code = runner(argv[1], argv[2], argv[3]);

	printf("%d 0x%x %d", error_code->incomplete, error_code->type, error_code->exit_code);

	return 0;
}

