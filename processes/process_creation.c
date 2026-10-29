#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // child process
        printf("Child: PID = %ld\n", (long)getpid());
        printf("Child: Parent PID = %ld\n", (long)getppid());
        fflush(stdout);

        _exit(0);
    } else {
        // parent process
        int status;

        printf("Parent: PID = %ld\n", (long)getpid());
        printf("Parent: Created child %ld\n", (long)pid);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n",
                   WEXITSTATUS(status));
        }
    }

    return 0;
}
