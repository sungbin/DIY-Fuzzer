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

void
timer_handler(int pid);

int
runner(int argc, char* argv[]) {
	printf(""); //for compiler to prevent removing printf
	out_fd = open("result.txt", O_WRONLY | O_APPEND, 755);
	signal(SIGALRM, timer_handler);
        int status;
        pid_t pid = fork();
        if(pid < 0) {
          return -1;
        }
	
        if (pid == 0) {
	  child_pid = pid;
          dup2(out_fd, STDOUT_FILENO); 
	  printf("\n\nINTPUT: %s\n", argv[1]); //TODO: multiple arguments
	  printf("OUTPUT: ");
	  execl(argv[0],argv[0],argv[1],NULL); // TODO: multiple arguments

          _exit(1);
        }

	alarm(100); //for timeout 100 seconds

        /* Parent process */
	if ( waitpid(pid, &status, 0) == -1 ) {
		perror("waitpid failed");
		return 1;
	}

	if ( WIFEXITED(status) ) {
		const int es = WEXITSTATUS(status);

		if(es != 0) {
			printf("INPUT: %s - Fail\n", argv[1]); // TODO: multiple arguments
		} else {
			printf("INPUT: %s - Pass\n", argv[1]); // TODO: multiple arguments
		}
	}

	close(out_fd);
        return 0;
}

void
timer_handler(int pid) {
	printf("Fail (TIMEOUT)\n");
	close(out_fd);
	kill(child_pid, SIGKILL);
}
