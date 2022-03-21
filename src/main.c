#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "../include/runner.h"

void
explore_dir_with_runner (char * input_dir_path, char * sub_dir, runner_error_code (*_runner)(char*, char*, char*, int), char * target_path, char * output_dir_path, int recursive_dir, int is_bcov);

int
mkdirs (char * dir_path);

char *
parent_dir (char * dir_path);

int 
main (int argc, char* argv[])
{

	if (argc < 4) {
                fprintf(stderr, "ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN THREE!\n");
                exit(1);
        }

	int is_bcov = 0;
	if (strcmp(argv[1], "-bcov") == 0) {
		is_bcov = 1;
		explore_dir_with_runner(argv[3], "",  &runner, argv[2], argv[4], 0, is_bcov);
	}
	else if (strcmp(argv[4], "-bcov") == 0) {

		is_bcov = 1;
		explore_dir_with_runner(argv[2], "",  &runner, argv[1], argv[3], 0, is_bcov);
	}
	else {

		// argv[1]: target_path;
		// argv[2]: input_dir_path;
		// argv[3]: output_dir_path;
		is_bcov = 0;
		explore_dir_with_runner(argv[2], "",  &runner, argv[1], argv[3], 0, is_bcov);
	}


	return 0;
}

void
explore_dir_with_runner (char * input_dir_path, char * sub_dir, runner_error_code (*_runner)(char*, char*, char*, int), char * target_path, char * output_dir_path, int recursive_dir, int is_bcov) {

	char * inner_dir_path;

	int sub_dir_len = strlen(sub_dir);
	if(sub_dir_len > 0) {

		int inner_dir_path_len = strlen(input_dir_path)+sub_dir_len+2;
		inner_dir_path = malloc(sizeof(char) * inner_dir_path_len);
		snprintf(inner_dir_path, inner_dir_path_len, "%s/%s", input_dir_path, sub_dir);
	
	}
	else {

		inner_dir_path = strdup(input_dir_path);

	}

        DIR * dp = opendir(inner_dir_path);
        struct dirent *ep;

        if (dp != NULL) {
                while ((ep = readdir(dp))) {
                        if (strcmp(ep->d_name,".") == 0) {
                                continue;
                        }
                        if (strcmp(ep->d_name,"..") == 0) {
                                continue;
                        }

			char * sub_child_dir;
			if (sub_dir_len > 0) {

				int sub_child_dir_len = strlen(sub_dir)+strlen(ep->d_name)+2;
				sub_child_dir = malloc(sizeof(char) * sub_child_dir_len);
				snprintf(sub_child_dir, sub_child_dir_len, "%s/%s", sub_dir, ep->d_name);

			}
			else {

				sub_child_dir = strdup(ep->d_name);

			}

			char * input_path, * program_out_path;
			int input_path_len, program_out_path_len; 

			input_path_len = strlen(input_dir_path)+strlen(sub_child_dir)+2;
			program_out_path_len = strlen(output_dir_path)+strlen(sub_child_dir)+2;

			input_path = malloc(sizeof(char) * input_path_len);
			program_out_path = malloc(sizeof(char) * program_out_path_len);
			
			snprintf(input_path, input_path_len, "%s/%s", input_dir_path, sub_child_dir);
			snprintf(program_out_path, program_out_path_len, "%s/%s", output_dir_path, sub_child_dir);

			if (mkdirs(dirname(program_out_path))) {
				fprintf(stderr, "ERROR: cannot mkdirs %s\n", dirname(dirname(program_out_path)));
			}

			runner_error_code error_code = (*_runner)(target_path, input_path, program_out_path, is_bcov);

			if (error_code.type == NO_ERROR) {
				printf("Input: %s\n", input_path);
				printf("-> Output: %s\n\n", program_out_path);
			}
			else {
				printf("Fail to run with: %s\n", input_path);
			}

                        if (recursive_dir && ep->d_type == DT_DIR) {

				explore_dir_with_runner(input_dir_path, "",  &runner, target_path, output_dir_path, 0, is_bcov);

                        } 

			free(sub_child_dir);
			free(input_path);
			free(program_out_path);
                }
                closedir(dp);
        }
        else {

		fprintf(stderr, "Couldn't open the directory: %s \n", inner_dir_path);
                exit(1);

        }

	free(inner_dir_path);

}
char *
parent_dir (char * path) {

	int lidx = strrchr(path, '/') - path;
	char * parent_dir_path = malloc(lidx * sizeof(char));
	strncpy(parent_dir_path, path, lidx);

	return parent_dir_path;
}

int
mkdirs (char * dir_path) {

	char * p_dir;
	if (access(dir_path, F_OK) == 0) {
		/* already exists*/
		return 0;
	}
	else if (access((p_dir=parent_dir(dir_path)), F_OK) == 0) {
		free(p_dir);
		return mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	else {

		int val = mkdirs(p_dir) || mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		free(p_dir);
		return val;
	}
}
