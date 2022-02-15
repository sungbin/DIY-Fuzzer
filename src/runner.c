#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int child_pid = 0;
int out_fd;

int
runner(char* program_path, char* in_str) {

	printf(""); //for compiler to prevent removing printf
	out_fd = open("result.txt", O_WRONLY | O_APPEND, 755);
        int status;
        pid_t pid = fork();
        if(pid < 0) {
          return -1;
        }
	
        if (pid == 0) {
	  child_pid = pid;
          dup2(out_fd, STDOUT_FILENO); 
	  printf("\n\nINTPUT: %s\n", in_str); //TODO: multiple arguments
	  printf("OUTPUT: ");
	  execl(program_path,program_path,in_str,NULL); // TODO: multiple arguments

          _exit(1);
        }

        /* Parent process */
	if ( waitpid(pid, &status, 0) == -1 ) {
		perror("waitpid failed");
		return 1;
	}

	close(out_fd);

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

