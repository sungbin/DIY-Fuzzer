#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include<fcntl.h>

int
runner (char *target_path, char *input_path, char *output_path) {

	pid_t pid = fork();
        if (pid < 0) { 
                return -1; //TODO: fork ERROR
        }

        
        /* Child process */
        int c_pid; 
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
                        int ret = kill(c_pid, SIGKILL);
                        if (! ret) {
                                // success to kill
                                return 1; //TODO:
                        }
			else {
                                // fail to kill
                                return 1; //TODO:
                        }
                }
                
                int rc = waitpid(pid, &status, WNOHANG);
                if (rc == -1) {
                        return 1; //TODO: waitpid ERROR
                }

                if (WIFEXITED(status)) {
                        int exit_stated = WEXITSTATUS(status);
                        return 0; //TODO: exit_status
                }

                end = ((int)clock()) / CLOCKS_PER_SEC;
        }

        return 0;
}

