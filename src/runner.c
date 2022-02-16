//#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include<fcntl.h>

int
runner(char* target_path, char* input_path) {

	pid_t pid = fork();
        if(pid < 0) {
		printf("fork fail\n");
		return -1;
        }


	// child
	if (pid == 0) {

		int input_fd = open(input_path, O_RDONLY);
//		printf("infd: %d ", input_fd);
		int out_fd = open("result.txt", O_WRONLY | O_CREAT, 755);
//		printf(", outfd: %d \n", out_fd);

		dup(input_fd);
		dup(out_fd); 

		close(STDIN_FILENO);
		close(STDOUT_FILENO);

		//dup2(input_fd, STDIN_FILENO);
		//dup2(out_fd, STDOUT_FILENO); 
		
		execl(target_path, target_path, NULL); // TODO: multiple arguments
		_exit(1);
        }

        /* Parent process */
	int status = 0;
	if ( waitpid(pid, &status, 0) == -1 ) {
		return 1;
	}

	if ( WIFEXITED(status) ) {
		const int es = WEXITSTATUS(status);

		if(es != 0) {
			return 1;
		} else {
			return 0;
		}
	}

        return 0;
}

