#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int boxes[100];
int million = 0;

void* search(void* threadID)
{
    int cycles = 33;
    int thread = (int)(threadID);
    int found = 0;
    int box;

    printf("Thread %d has started searching for the million\n", thread + 1);
    srand(time(NULL));

    while (cycles > 0 && million == 0) {
        box = rand() % 100;

        if (boxes[box] == 1000000) {
            printf("Thread %d has found the million in %d cycles\n", thread + 1, 33 - cycles);
            million = 1;
            found = 1;
        }

        --cycles;
    }

    if (cycles == 0 || (million == 1 && found == 0)) {
        printf("Thread %d didn't find the million\n", thread + 1);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[5];
    void* status;
    int i, check;

    for (i = 1; i <= 100; ++i) {
        boxes[i - 1] = 10000 * i;
    }

    for (i = 0; i < 5; ++i) {
        check = pthread_create(&threads[i], NULL, search, (void*)(i));

        if (check != 0) {
            printf("Error occurred while creating threads %d\n", i);
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

    pthread_exit(NULL);
}