#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс

        execl("./sequential_min_max",
              "./sequential_min_max",
              "20", "42",
              NULL);

        perror("execl");
        exit(1);
    }

    // Родительский процесс

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child exited with code %d\n", WEXITSTATUS(status));
    }

    return 0;
}