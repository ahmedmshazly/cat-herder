#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

void close_fds_except(int keep_fds[], int num_fds) {
    for (int fd = 0; fd < 1024; fd++) {
        int should_close = 1;
        for (int i = 0; i < num_fds; i++) {
            if (fd == keep_fds[i]) {
                should_close = 0;
                break;
            }
        }
        if (should_close) {
            close(fd);
        }
    }
}

void setup_environment(int kitty_version) {
    if (kitty_version == 2) {
        setenv("CATFOOD", "yummy", 1);
    } else if (kitty_version == 3) {
        unsetenv("KITTYLITTER");
    } else if (kitty_version == 4) {
        // clean environment start
        char *path = strdup(getenv("PATH")); 
        char *home = strdup(getenv("HOME")); 
        clearenv();
        if (path) setenv("PATH", path, 1);
        if (home) setenv("HOME", home, 1);
        setenv("CATFOOD", "yummy", 1);
        free(path); // free   duplicated strings
        free(home);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    // redirection of input & output
    int input_fd = open(argv[1], O_RDONLY);
    int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (input_fd == -1 || output_fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // 1st child (kitty -2)
        dup2(input_fd, 0);
        dup2(pipe1[1], 1);
        int fds_to_keep[] = {0, 1, 2};
        close_fds_except(fds_to_keep, 3);
        setup_environment(2);
        execlp("kitty", "kitty", "-2", NULL);
        perror("Failed to exec kitty -2");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // 2nd child (kitty -3)
        dup2(pipe1[0], 0);
        dup2(pipe2[1], 1);
        int fds_to_keep[] = {0, 1, 2};
        close_fds_except(fds_to_keep, 3);
        setup_environment(3);
        execlp("kitty", "kitty", "-3", NULL);
        perror("Failed to exec kitty -3");
        exit(1);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        // 3rd child (kitty -4)
        dup2(pipe2[0], 0);
        dup2(output_fd, 1);
        int fds_to_keep[] = {0, 1, 2};
        close_fds_except(fds_to_keep, 3);
        setup_environment(4);
        execlp("kitty", "kitty", "-4", NULL);
        perror("Failed to exec kitty -4");
        exit(1);
    }

    close(input_fd);
    close(output_fd);
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    int status, result = 0;
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) result = 1;

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) result = 1;

    waitpid(pid3, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) result = 1;

    return result;
}
