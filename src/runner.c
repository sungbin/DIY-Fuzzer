#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "../include/runner.h"
#include "../include/trace-pc.h"

FILE * bcov_fp = 0x0;

runner_error_code
get_error (enum E_Type type, int exit_code);

runner_error_code
runner (char* target_path, char* input_path, char *output_path, int is_bcov) {

	char * bcov_path;
	if (is_bcov) {
		char * f_name = basename(input_path);
		char * d_name = dirname(output_path);
		bcov_path = malloc(sizeof(char) * (strlen(f_name) + strlen(d_name) + 7));
		sprintf(bcov_path, "%s/%s.bcov", d_name, f_name);
		bcov_fp = fopen(bcov_path, "wb");
	}

	printf("@ in: %s\n@ out: %s\n", input_path, output_path);

	pid_t pid = fork();
        if (pid < 0) { 
		runner_error_code error_code = get_error(E_FORK, 0);
	       return error_code;
        }

        /* Child process */
        if (pid == 0) { 

	       int input_fd = open(input_path, O_RDONLY);
	       int out_fd = open(output_path, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	       
	       //dup2(input_fd, STDIN_FILENO);
	       //dup2(out_fd, STDOUT_FILENO);
	       //while (dup2(input_fd, STDIN_FILENO) == -1) { };
	       //while (dup2(out_fd, STDOUT_FILENO) == -1) { };
	       if (dup2(input_fd, STDIN_FILENO) == -1) {
		       perror("dup2-input");
	       }
	       if (dup2(out_fd, STDOUT_FILENO) == -1) {
		       perror("dup2-output");
	       }

	       execl(target_path, target_path, NULL);
	       _exit(1);
        }

	/* Parent process */
        int status = 0;
        int start, end;
        start = ((int)clock()) / CLOCKS_PER_SEC;
        end = ((int)clock()) / CLOCKS_PER_SEC;

        while ((end - start) < 10) {
		int w = waitpid(pid, &status, WNOHANG);
		if (w != 0) {
			break;
		}
	       end = ((int)clock()) / CLOCKS_PER_SEC;
	}

	if (is_bcov) {
		fclose(bcov_fp);
		free(bcov_path);
	}

	int exit_stated = WEXITSTATUS(status);
	if ((end - start) >= 1) {
		// Time out Kill
		kill(pid, SIGKILL);
		wait(&status);
		runner_error_code error_code = get_error(E_TIMEOUT_KILL, exit_stated);
		return error_code;
	}
	else {
		// normally exit
		runner_error_code error_code = get_error(NO_ERROR, exit_stated);
		return error_code;
	}
}

runner_error_code
get_error (enum E_Type type, int exit_code) {
	runner_error_code _code;
	_code.type = type;
	_code.exit_code = exit_code;

	return _code;
}
