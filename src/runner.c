#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "../include/runner.h"

runner_error_code
get_error (int incomplete, int type, int exit_code);

runner_error_code
runner (char *target_path, char *input_path, char *output_path)
{
	pid_t pid = fork();
        if (pid < 0) { 
		runner_error_code error_code = get_error(1, E_FORK, 0);
                return error_code;
        }

        /* Child process */
        if (pid == 0) { 
                c_pid = pid; 
                int input_fd = open(input_path, O_RDONLY);
                int out_fd = open(output_path, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
                
                dup2(input_fd, STDIN_FILENO);
                dup2(out_fd, STDOUT_FILENO);
                
                execl(target_path, target_path, NULL);
                _exit(1);
        }
        
        /* Parent process */
        int start, end;
        start = ((int)clock()) / CLOCKS_PER_SEC;
        end = ((int)clock()) / CLOCKS_PER_SEC;

        
        int status = 0;
        while (1) {
                if ((end - start) > 10) {
                        int ret = kill(pid, SIGKILL);
                        if (! ret) {
                                // success to kill
                                return 1; //TODO:
                        }
			else {
                                // fail to kill
				runner_error_code error_code = get_error(1, E_CANNOT_KILL, 0);
                                return error_code; 
                        }
                }
                
                int rc = waitpid(pid, &status, WNOHANG);

                if (! WIFEXITED(status)) {
                        int exit_stated = WEXITSTATUS(status);
			runner_error_code error_code = get_error(1, 0, exit_stated);
			return error_code; 
                }

                end = ((int)clock()) / CLOCKS_PER_SEC;
        }

	runner_error_code error_code = get_error(0, 0, 0);
	return error_code; 
}

runner_error_code
get_error (int incomplete, int type, int exit_code) {
	
	runner_error_code _code = malloc(sizeof(struct_runner_error_code));
	_code->incomplete = incomplete;
	_code->type = type;
	_code->exit_code = exit_code;

	return _code;
}
