#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int array[1000];

void* search(void* threadID)
{
    int thread = (int)(threadID);
    int count = 0;
    int i;

    for (i = thread * 100; i < (thread * 100 + 100); ++i) {
        if (array[i] == 0) {
            ++count;
        }
    }

    printf("Thread %d found %d zeros\n", thread, count);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pid_t children[2];
    pid_t subChildren[10];
    pthread_t threads[10];
    void* status;
    int secondsProcesses = 0;
    int processesFinished = 0;
    int secondsThreads = 0;
    int threadsFinished = 0;
    int count = 0;
    int i, j, k, check;

    for (i = 0; i < 1000; ++i) {
        array[i] = rand() % 10;
    }

    for (i = 0; i < 2; ++i) {
        children[i] = fork();

        if (children[i] == 0) {
            break;
        }
    }

    if (i < 2) {
        if (i == 0) {
            for (j = 0; j < 10; ++j) {
                subChildren[j] = fork();

                if (subChildren[j] == 0) {
                    break;
                }
            }

            if (j < 10) {
                for (k = j * 100; k < (j * 100 + 100); ++j) {
                    if (array[k] == 0) {
                        ++count;
                    }
                }

                printf("Child process %d of the first process found %d zeros\n", j, count);
            }
            else {
                for (j = 0; j < 10; ++j) {
                    waitpid(subChildren[j], NULL, WAIT_MYPGRP);
                }
            }
        }
        else if (i == 1) {
            for (j = 0; j < 10; ++j) {
                check = pthread_create(&threads[j], NULL, search, (void*)(j));

                if (check != 0) {
                    printf("Error occurred while creating thread %d\n", j);
                    exit(-1);
                }
            }

            for (j = 0; j < 10; ++j) {
                check = pthread_join(threads[j], &status);

                if (check != 0) {
                    printf("Error occurred while waiting for thread %d\n", j);
                    exit(-1);
                }
            }
        }
    }
    else {
        while (processesFinished == 0 && threadsFinished == 0) {
            if (waitpid(children[0], NULL, WNOHANG) == children[0]) {
                processesFinished = 1;
            }

            if (waitpid(children[1], NULL, WNOHANG) == children[1]) {
                threadsFinished = 1;
            }

            sleep(1);

            if (processesFinished == 0) {
                ++secondsProcesses;
            }

            if (threadsFinished == 0) {
                ++secondsThreads;
            }
        }

        if (secondsProcesses > secondsThreads) {
            printf("The quicker way to perform the search is with threads\n");
        }
        else {
            printf("The quicker way to perform the search is with processes\n");
        }
    }

    return 0;
}