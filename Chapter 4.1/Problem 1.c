#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t child;
    int seconds = 0;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line!\n");
        exit(-1);
    }

    child = fork();

    if (child == 0) {
        execvp(argv[1], &argv[1]);
        printf("Function call to execute command was not successful!\n");
    }
    else {
        while (1) {
            if (waitpid(child, NULL, WNOHANG) == child) {
                break;
            }

            sleep(1);
            ++seconds;
        }

        printf("The child process executed the command in %d seconds\n", seconds);
    }

    return 0;
}