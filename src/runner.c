#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "../include/runner.h"

runner_error_code
get_error (enum E_Type type, int exit_code);

runner_error_code
runner (char *target_path, char *input_path, char *output_path)
{
	pid_t pid = fork();
        if (pid < 0) { 
		runner_error_code error_code = get_error(E_FORK, 0);
                return error_code;
        }

        /* Child process */
        if (pid == 0) { 
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

        

        while ((end - start) < 10) {
                end = ((int)clock()) / CLOCKS_PER_SEC;
	}

        int status = 0;
	waitpid(pid, &status, WNOHANG);
        if (WIFEXITED(status)) {
		int exit_stated = WEXITSTATUS(status);
		runner_error_code error_code = get_error(0, exit_stated);
		return error_code;
	}
	else {
		int ret = kill(pid, SIGKILL);
		runner_error_code error_code = get_error(E_TIMEOUT_KILL, 0);
		return error_code; 
	}

	/* cannot reach this area*/
}

runner_error_code
get_error (enum E_Type type, int exit_code) {
	runner_error_code _code;
	_code.type = type;
	_code.exit_code = exit_code;

	return _code;
}
