#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int array[100];

typedef struct limit {
    int K;
    int M;
} limit;

void* increment(void* limits)
{
    limit threadLimit = *(limit*)(limits);
    int i;

    for (i = threadLimit.K; i < threadLimit.M; ++i) {
        ++array[i];
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pid_t child;
    pthread_t threads[100];
    limit threadLimit;
    void* status;
    int count = 0;
    int i, check, K, M, N;

    child = fork();

    if (child == 0) {
        for (i = 0; i < 100; ++i) {
            array[i] = 0;
        }

        printf("Please enter an amount for the number of threads you want to run\n");
        scanf("%d", &N);
        srand(time(NULL));

        for (i = 0; i < N; ++i) {
            K = rand() % 100;
            M = rand() % 100;

            if (K < M) {
                threadLimit.K = K;
                threadLimit.M = M;
            }
            else {
                threadLimit.K = M;
                threadLimit.M = K;
            }

            check = pthread_create(&threads[i], NULL, increment, (void*)(&threadLimit));

            if (check != 0) {
                printf("Error occurred while creating thread %d\n", i);
                exit(-1);
            }
        }

        for (i = 0; i < N; ++i) {
            check = pthread_join(threads[i], &status);

            if (check != 0) {
                printf("Error occurred while waiting for thread %d\n", i);
                exit(-1);
            }
        }

        for (i = 0; i < 100; ++i) {
            if (array[i] > 1) {
                ++count;
            }
        }

        printf("There have been %d overlaps between the limits\n", count);
    }
    else {
        waitpid(child, NULL, WAIT_MYPGRP);
    }

    return 0;
}