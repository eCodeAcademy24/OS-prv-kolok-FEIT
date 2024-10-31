#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

FILE* file;
int upperCase[100];
int lowerCase[100];

void* count(void* threadID)
{
    int thread = (int)(threadID);
    int lineCount = thread;
    int i = 0;
    int j;
    char line[1000];

    fseek(file, 0, SEEK_SET);

    if (lineCount > 0) {
        lineCount *= 10;

        while (i < lineCount && (fgets(line, 1000, file) != NULL)) {
            ++i;
        }

        if (i == lineCount) {
            lineCount += 10;

            while (i <= lineCount && (fgets(line, 1000, file) != NULL)) {
                j = 0;

                while (line[j] != '\0' && line[j] != '\n') {
                    if (isalpha[line[j]] && isupper(line[j])) {
                        ++upperCase[thread];
                    }
                    else if (isalpha(line[j]) && islower(line[j])) {
                        ++lowerCase[thread];
                    }

                    ++j;
                }

                ++i;
            }
        }
    }
    else {
        lineCount += 10;

        while (i <= lineCount && (fgets(line, 1000, file) != NULL)) {
            j = 0;

            while (line[j] != '\0' && line[j] != '\n') {
                if (isalpha[line[j]] && isupper(line[j])) {
                    ++upperCase[thread];
                }
                else if (isalpha(line[j]) && islower(line[j])) {
                    ++lowerCase[thread];
                }

                ++j;
            }

            ++i;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[100];
    void* status;
    int lines = 0;
    int N = 1;
    int i, check;
    char line[1000];

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line\n");
        exit(-1);
    }

    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open file for reading\n");
        exit(-1);
    }

    while (fgets(line, 1000, file) != NULL) {
        ++lines;
    }

    N += (lines / 10);

    for (i = 0; i < N; ++i) {
        upperCase[i] = 0;
        lowerCase[i] = 0;
    }

    for (i = 0; i < N; ++i) {
        check = pthread_create(&threads[i], NULL, count, (void*)(i));

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
        printf("Thread %d found %d uppercase and %d lowercase letters\n", i, upperCase[i], lowerCase[i]);
    }

    return 0;
}