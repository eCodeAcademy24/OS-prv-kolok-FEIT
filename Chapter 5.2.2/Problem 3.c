#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int array[1000];
int even[1000];
int odd[1000];
int final[1000];
int evenNumbers = 0;
int oddNumbers = 0;
int totalNumbers = 0;
int N;

void* sort(void* threadID)
{
    int thread = (int)(threadID);
    int i, j, tmp;

    if (thread == 0) {
        for (i = 0; i < N; ++i) {
            if (array[i] % 2 == 0) {
                even[evenNumbers++] = array[i];
            }
        }

        for (i = 0; i < evenNumbers - 1; ++i) {
            for (j = 0; j < evenNumbers; ++j) {
                if (even[i] > even[j]) {
                    tmp = even[i];
                    even[i] = even[j];
                    even[j] = tmp;
                }
            }
        }
    }
    else if (thread == 1) {
        for (i = 0; i < N; ++i) {
            if (array[i] % 2 == 1) {
                odd[oddNumbers++] = array[i];
            }
        }

        for (i = 0; i < oddNumbers - 1; ++i) {
            for (j = 0; j < oddNumbers; ++j) {
                if (odd[i] > odd[j]) {
                    tmp = odd[i];
                    odd[i] = odd[j];
                    odd[j] = tmp;
                }
            }
        }
    }
    else if (thread == 2) {
        for (i = 0; i < evenNumbers; ++i) {
            final[totalNumbers++] = even[i];
        }

        for (i = 0; i < oddNumbers; ++i) {
            final[totalNumbers++] = odd[i];
        }

        for (i = 0; i < totalNumbers - 1; ++i) {
            for (j = 0; j < totalNumbers; ++j) {
                if (final[i] > final[j]) {
                    tmp = final[i];
                    final[i] = final[j];
                    final[j] = tmp;
                }
            }
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[3];
    void* status;
    int i, check;

    printf("Please enter the length of the array\n");
    scanf("%d", &N);
    srand(time(NULL));

    for (i = 0; i < N; ++i) {
        array[i] = rand() % 10000;
    }

    for (i = 0; i < 2; ++i) {
        check = pthread_create(&threads[i], NULL, sort, (void*)(i));

        if (check != 0) {
            printf("Error occurred while creating thread %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < 2; ++i) {
        check = pthread_join(threads[i], &status);

        if (check != 0) {
            printf("Error occurred while waiting for thread %d\n", i);
            exit(-1);
        }
    }

    check = pthread_create(&threads[2], NULL, sort, (void*)(2));

    if (check != 0) {
        printf("Error occurred while creating final thread\n");
        exit(-1);
    }

    check = pthread_join(threads[2], &status);

    if (check != 0) {
        printf("Error occurred while waiting for final thread\n");
        exit(-1);
    }

    for (i = 0; i < totalNumbers - 1; ++i) {
        printf("%d, ", final[i]);
    }

    printf("%d\n", final[i]);
    return 0;
}