#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t children[100];
    int i, wait, N;
    char* command, firstArgument, secondArgument, thirdArgument;

    command = (char*)malloc(10 * sizeof(char));
    firstArgument = (char*)malloc(10 * sizeof(char));
    secondArgument = (char*)malloc(10 * sizeof(char));
    thirdArgument = (char*)malloc(10 * sizeof(char));

    srand(time(NULL));

    printf("Please enter the number of children processes you want to create\n");
    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        printf("Please enter the command and the arguments\n");
        scanf("%s %s %s %s", &command[0], &firstArgument[0], &secondArgument[0],  &thirdArgument[0]);

        children[i] = fork();

        if (children[i] == 0) {
            break;
        }
    }

    if (i < N) {
        wait = rand() % 20 + 1;
        printf("Child process %d will wait %d seconds before executing\n", i, wait);

        sleep(wait);
        execlp(command, command, firstArgument, secondArgument, thirdArgument, NULL);
        printf("Function call to execute command was not siccessful!\n");
    }
    else {
        printf("Waiting for the children processes\n");

        for (i = 0; i < N; ++i) {
            waitpid(children[i], NULL, WAIT_MYPGRP);
        }

        printf("All of the children processes have finished executing\n");
    }

    return 0;
}