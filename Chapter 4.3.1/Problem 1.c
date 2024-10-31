#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int array[100];

void* increment(void* cycles)
{
    int K = (int)(cycles);
    int i, position;

    srand(time(NULL));

    for (i = 0; i < K; ++i) {
        position = rand() % 100;
        ++array[position];
    }

    pthread_exit(NULL);
}

void* decrement(void* cycles)
{
    int K = (int)(cycles);
    int i, position;

    srand(time(NULL));

    for (i = 0; i < K; ++i) {
        position = rand() % 100;
        --array[position];
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pid_t child;
    pthread_t threads[100];
    void* status;
    int counter = 0;
    int i, N, check, cycles;

    child = fork();

    if (child == 0) {
        for (i = 0; i < 100; ++i) {
            array[i] = 0;
        }

        printf("Please enter the amount of threads you want to create\n");
        scanf("%d", &N);

        srand(time(NULL));

        for (i = 0; i < N; ++i) {
            cycles = rand() % 500 + 1;

            if (i < N / 2) {
                check = pthread_create(&threads[i], NULL, increment, (void*)(cycles));

                if (check != 0) {
                    printf("Error occurred while creating thread %d\n", i);
                    exit(-1);
                }
            }
            else {
                check = pthread_create(&threads[i], NULL, decrement, (void*)(cycles));

                if (check != 0) {
                    printf("Error occurred while creating thread %d\n", i);
                    exit(-1);
                }
            }
        }

        for (i = 0; i < N; ++i) {
            check = pthread_join(threads[i], &status);

            if (check != 0) {
                printf("Error occurred while waiting for thread %d\n", i);
            }
        }

        for (i = 0; i < 100; ++i) {
            if (array[i] != 0) {
                ++counter;
            }
        }

        printf("%d numbers have changed their value\n", counter);
    }
    else {
        waitpid(child, NULL, WAIT_MYPGRP);
    }

    return 0;
}