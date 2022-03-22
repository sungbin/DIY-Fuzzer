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

unsigned int total_branch;

typedef struct _bcov_set {
	unsigned int pc;
	struct _bcov_set * next;

} bcov_set;

typedef struct _bcov {
	unsigned int pc;
	unsigned int des_len;
	char des[1024];
	struct _bcov * next;
} bcov;


bcov_set * b_set = 0x0;

void
update_branch_set (bcov_set * _set, unsigned int pc);

bcov*
read_bcov (char * bcov_path);

void
print_branch_set (bcov_set * _set);

void
print_bcov (bcov * b);

void
free_set (bcov_set * b_set);

void
free_bcov (bcov * b);

int 
main (int argc, char* argv[])
{

	int is_bcov;
	if (argc < 4) {
                fprintf(stderr, "ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN THREE!\n");
                exit(1);
        }
	else if (argc == 4) {

		// argv[1]: target_path;
		// argv[2]: input_dir_path;
		// argv[3]: output_dir_path;
		is_bcov = 0;
		explore_dir_with_runner(argv[2], "",  &runner, argv[1], argv[3], 0, is_bcov);
	}
	else if (strcmp(argv[1], "-bcov") == 0) {

		is_bcov = 1;
		explore_dir_with_runner(argv[3], "",  &runner, argv[2], argv[4], 0, is_bcov);
		print_branch_set(b_set);
		free_set(b_set);
	}
	else if (strcmp(argv[4], "-bcov") == 0) {

		is_bcov = 1;
		explore_dir_with_runner(argv[2], "",  &runner, argv[1], argv[3], 0, is_bcov);
		print_branch_set(b_set);
		free_set(b_set);
	}
	else {
                fprintf(stderr, "ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN THREE!\n");
                exit(1);
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

			char * p_dir = parent_dir(program_out_path);
			if (mkdirs(p_dir)) {
				fprintf(stderr, "ERROR: cannot mkdirs %s\n", dirname(dirname(program_out_path)));
			}
			free(p_dir);

			runner_error_code error_code = (*_runner)(target_path, input_path, program_out_path, is_bcov);

			if (error_code.type == NO_ERROR) {
				printf("Input: %s\n", input_path);
				printf("Output: %s\n\n", program_out_path);
				
				//read bcov
				char * bcov_path = malloc(sizeof(char) * (strlen(program_out_path) + 6));
				sprintf(bcov_path, "%s.bcov", program_out_path);
				bcov * b = read_bcov(bcov_path);

				printf("branch-coverage of %s:\n", bcov_path);
				print_bcov(b);

				free_bcov(b);
				free(bcov_path);
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

// need to free()
char *
parent_dir (char * path) {

	char * p = strrchr(path, '/');
	if (p == 0x0) {
		fprintf(stderr,"strrchr error!\n");
		exit(1);
	}
	int lidx = p - path;
	char * parent_dir_path = malloc((lidx+1) * sizeof(char));
	strncpy(parent_dir_path, path, lidx);
	parent_dir_path[lidx] = 0x0;

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

bcov*
read_bcov (char * bcov_path) {

	FILE * bcov_fp = fopen(bcov_path, "rb");
	fread(&total_branch, 1, 4, bcov_fp);
	int buf_len = 0;

	bcov * b = 0x0;
	bcov * last_b = 0x0;
	do {
		unsigned int pc;
		buf_len = fread(&pc, 1, 4, bcov_fp);
		if (buf_len != 4) break;

		unsigned int des_len;
		buf_len = fread(&des_len, 1, 4, bcov_fp);
		if (buf_len != 4) break;

		char des[1024];
		buf_len = fread(des, 1, des_len, bcov_fp);
		if (buf_len != des_len) break;

		//printf("read: %s\npc:%u, des_len:%u, des: %s\n",bcov_path, pc, des_len, des);

		if (b  == 0x0) {
			b = malloc(sizeof(bcov));
			b->pc = pc;
			b->des_len = des_len;
			strcpy(b->des, des);
			b->next = 0x0;
			last_b = b;
		}
		else {
			bcov * _b = malloc(sizeof(bcov));
			_b->pc = pc;
			_b->des_len = des_len;
			strcpy(b->des, des);
			_b->next = 0x0;
			last_b->next = _b;
			last_b = _b;
		}
		update_branch_set(b_set, pc);

	} while(buf_len > 0);

	fclose(bcov_fp);
	return b;
}
void
update_branch_set (bcov_set * _set, unsigned int pc) {

	bcov_set * __set = _set;
	while (__set != 0x0) {
		if(__set->pc == pc) {
			break;
		}
		else {
			__set = __set->next;
		}
	}
	if (_set == 0x0) {
		__set = malloc(sizeof(bcov_set));
		__set->pc = pc;
		__set->next = 0x0;
		b_set = __set;
	}
	else if (__set == 0x0) {
		__set = _set;
		while(__set->next != 0x0) { __set = __set->next;}
		__set->next = malloc(sizeof(bcov_set));
		__set->next->pc = pc;
		__set->next->next = 0x0;

	}
	else {
		// already exists
	}
	
}
void
print_branch_set (bcov_set * _set) {
	printf("Total branch Coverage of All inputs:\n");
	unsigned int n = 0;
	printf("{");
	bcov_set * _b = _set;
	while (_b != 0x0) {
		printf("%u, ", _b->pc);
		_b = _b->next;
		n++;
	}
	printf("\b\b}\n");
	printf("%.1f%% (%u/%u)\n", (float) n*100 / (float) total_branch, n, total_branch);
}


void
print_bcov (bcov * b) {
	unsigned int n = 0;
	printf("{");
	bcov * _b = b;
	while (_b != 0x0) {
		printf("%u, ", _b->pc);
		_b = _b->next;
		n++;
	}
	printf("\b\b}\n");
	printf("%.1f%% (%u/%u)\n\n", (float) n*100 / (float) total_branch, n, total_branch);
}

void
free_set (bcov_set * b_set) {

	bcov_set * next;
	while (b_set != 0x0) {
		next = b_set->next;
		free(b_set);
		b_set = next;
	}
}
void
free_bcov (bcov * b) {
	bcov * next;
	while (b != 0x0) {
		next = b->next;
		free(b);
		b = next;
	}
}
