#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int array[30] = {1, 5, 11, 15, 13, 17, 19, 22, 20, 7, 100, 96, 46, 31, 36, 87, 75, 53, 59, 60, 88, 65, 41, 47, 72, 49, 99, 71, 83, 4};

int main(int argc, char* argv[])
{
    pid_t children[5];
    int i, j, number, start, end, tmp;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line\n");
        exit(-1);
    }

    number = atoi(argv[1]);

    for (i = 0; i < 5; ++i) {
        children[i] = fork();

        if (children[i] == 0) {
            break;
        }
    }

    if (i < 5) {
        srand(time(NULL));

        start = rand() % 30;
        end = rand() % 30;

        if (start > end) {
            tmp = end;
            end = start;
            start = tmp;
        }

        for (j = start; j < end; ++j) {
            if (array[j] == guess) {
                printf("The number was found by a thread in the range between %d and %d\n", start, end);
                break;
            }
        }

        if (j == end) {
            printf("The number was not found by a thread in the range between %d and %d\n", start, end);
        }
    }
    else {
        for (i = 0; i < 5; ++i) {
            waitpid(threads[i], NULL, WAIT_MYPGRP);
        }
    }

    return 0;
}