
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        
        printf("Child process finished. PID: %d\n", getpid());
        exit(0);
    }
    else if (pid > 0) {
        // Родительский процесс

        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is sleeping for 30 seconds...\n");
        sleep(30);

        // Забираем статус завершения дочернего процесса
        waitpid(pid, NULL, 0);

        printf("Zombie process has been removed.\n");
    }
    else {
        // Ошибка создания процесса
        
        perror("fork");
        return 1;
    }

    return 0;
}
