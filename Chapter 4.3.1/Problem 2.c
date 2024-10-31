#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

pid_t children[10];
int times[10];

void* waitProcess(void* position)
{
    int process = (int)(position);
    int seconds = 0;

    while (1) {
        if (waitpid(children[process], NULL, WNOHANG) == children[process]) {
            break;
        }

        sleep(1);
        ++seconds;
    }

    times[process] = seconds;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[10];
    void* status;
    int N = argc - 1;
    int i, check;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line!\n");
        exit(-1);
    }

    for (i = 0; i < N; ++i) {
        children[i] = fork();

        if (children[i] == 0) {
            break;
        }
    }

    if (i < N) {
        execlp(argv[i + 1], argv[i + 1], NULL);
        printf("Unable to execute system call\n");
    }
    else {
        for (i = 0; i < N; ++i) {
            check = pthread_create(&threads[i], NULL, waitProcess, (void*)(i));

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

        for (i = 0; i < N; ++i) {
            printf("Thread %d counted that the process needed %d seconds to execute\n", i, times[i]);
        }
    }

    return 0;
}