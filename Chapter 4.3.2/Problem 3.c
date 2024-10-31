#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

char array[1000];
int characters = 0;

void* code(void* threadID)
{
    int thread = (int)(threadID);
    int start, end, result;

    if (thread < 5) {
        start = thread * characters / 6;
        end = (thread + 1) * characters / 6;

        while (start < end) {
            result = array[start] - array[start + 1];

            array[start] += result;
            ++start;
        }
    }
    else {
        start = thread * characters / 6;
        end = characters - 1;

        while (start < end) {
            result = array[start] - array[start + 1];

            array[start] += result;
            ++start;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[6];
    void* status;
    int i, check;
    char character;

    FILE* file;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line!\n");
        exit(-1);
    }

    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open file for reading!\n");
        exit(-1);
    }

    while ((character = fgetc(file)) != EOF) {
        if (isalnum(character)) {
            array[characters] = character;
            ++characters;
        }
    }

    for (i = 0; i < 6; ++i) {
        check = pthread_create(&threads[i], NULL, code, (void*)(i));

        if (check != 0) {
            printf("Error occurred while creating thread %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < 6; ++i) {
        check = pthread_join(threads[i], &status);

        if (check != 0) {
            printf("Error occurred while waiting for thread %d\n", i);
            exit(-1);
        }
    }

    printf("The content of the file after coding is\n");

    for (i = 0; i < characters; ++i) {
        printf("%c", array[i]);
    }

    printf("\n");
    pthread_exit(NULL);
}