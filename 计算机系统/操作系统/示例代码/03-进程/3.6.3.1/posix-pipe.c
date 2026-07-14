#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { READ_END = 0, WRITE_END = 1, BUFFER_SIZE = 64 };

int main(void)
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        close(pipe_fd[READ_END]);
        close(pipe_fd[WRITE_END]);
        return EXIT_FAILURE;
    }

    if (pid > 0) {
        const char message[] = "Greetings from the parent";
        close(pipe_fd[READ_END]);
        if (write(pipe_fd[WRITE_END], message, sizeof(message)) == -1) {
            perror("write");
        }
        close(pipe_fd[WRITE_END]);
        waitpid(pid, NULL, 0);
        return EXIT_SUCCESS;
    }

    char buffer[BUFFER_SIZE] = {0};
    close(pipe_fd[WRITE_END]);
    ssize_t count = read(pipe_fd[READ_END], buffer, sizeof(buffer) - 1);
    if (count < 0) {
        perror("read");
        close(pipe_fd[READ_END]);
        _exit(EXIT_FAILURE);
    }
    close(pipe_fd[READ_END]);
    printf("Child read: %s\n", buffer);
    return EXIT_SUCCESS;
}
