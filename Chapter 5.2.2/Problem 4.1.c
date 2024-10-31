#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int array[30] = {1, 5, 11, 15, 13, 17, 19, 22, 20, 7, 100, 96, 46, 31, 36, 87, 75, 53, 59, 60, 88, 65, 41, 47, 72, 49, 99, 71, 83, 4};

void* search(void* number)
{
    int guess = (int)(number);
    int i, start, end, tmp;

    srand(time(NULL));

    start = rand() % 30;
    end = rand() % 30;

    if (start > end) {
        tmp = end;
        end = start;
        start = tmp;
    }

    for (i = start; i < end; ++i) {
        if (array[i] == guess) {
            printf("The number was found by a thread in the range between %d and %d\n", start, end);
            break;
        }
    }

    if (i == end) {
        printf("The number was not found by a thread in the range between %d and %d\n", start, end);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pid_t child;
    pthread_t threads[5];
    void* status;
    int i, check, number;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line\n");
        exit(-1);
    }

    number = atoi(argv[1]);
    child = fork();

    if (child == 0) {
        execlp("./Problem 4.2", "./Problem 4.2", argv[1], NULL);
        printf("Invalid function call, program cannot be executed\n");
    }
    else {
        for (i = 0; i < 5; ++i) {
            check = pthread_create(&threads[i], NULL, search, (void*)(number));

            if (check != 0) {
                printf("Error occurred while creating thread %d\n", i);
                exit(-1);
            }
        }

        for (i = 0; i < 5; ++i) {
            check = pthread_join(threads[i], &status);

            if (check != 0) {
                printf("Error occurred while waiting for thread %d\n", i);
                exit(-1);
            }
        }
    }

    return 0;
}