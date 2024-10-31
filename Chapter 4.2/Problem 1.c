#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int numbers[1000];
int maximum = 0;

void* generate(void* threadID)
{
    int i;
    int thread = (int)(threadID);

    srand(time(NULL));

    for (i = thread * 100; i < (thread * 100 + 100); ++i) {
        numbers[i] = rand() % 1000;
    }

    pthread_exit(NULL);
}

void* search(void* threadID)
{
    int i;
    int thread = (int)(threadID);

    for (i = thread * 100; i < (thread * 100 + 100); ++i) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threadsGenerate[10], threadsSearch[10];
    void* status;
    int i, check;

    for (i = 0; i < 10; ++i) {
        check = pthread_create(&threadsGenerate[i], NULL, generate, (void*)(i));

        if (check != 0) {
            printf("Error occurred while creating thread %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < 10; ++i) {
        check = pthread_join(threadsGenerate[i], &status);

        if (check != 0) {
            printf("Error occurred while waiting for thread %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < 10; ++i) {
        check = pthread_create(&threadsSearch[i], NULL, search, (void*)(i));

        if (check != 0) {
            printf("Error occurred while creating thread %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < 10; ++i) {
        check = pthread_join(threadsSearch[i], &status);

        if (check != 0) {
            printf("Error occurred while waiting for thread %d\n", i);
            exit(-1);
        }
    }

    printf("The maximum element in the array is %d\n", maximum);
    pthread_exit(NULL);
}