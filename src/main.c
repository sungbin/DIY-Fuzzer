#include <stdio.h>
#include <string.h>

#include "../include/runner.h"

int 
main(int argc, char* argv[])
{

	if(argc < 2) {
                printf("ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN ONE!\n");
                return 1;
        }

	char in_str[1024];
        fgets(in_str, 1024, stdin);
        in_str[strlen(in_str) - 1] = '\0';

	int _blank_idx = 0;
	for(int _idx = 0; _idx < strlen(in_str); _idx++) {
		if(in_str[_idx] == ' ') {
			_blank_idx = _idx;
			break;
		}
	}
	char file_name[128];
	char input[1024];
	strncpy(file_name,in_str,_blank_idx);
	strncpy(input, (in_str+_blank_idx), strlen(in_str)-_blank_idx);

	if(! runner(file_name, input)) {
		/*  Pass: return 0 */
		printf("INPUT: %s - Pass\n", in_str); // TODO: multiple arguments

	} else {
		/*  Fail  */
		printf("INPUT: %s - Fail\n", in_str); // TODO: multiple arguments
	}


	return 0;
}


//int runner(char* program_path, char* in_str);
