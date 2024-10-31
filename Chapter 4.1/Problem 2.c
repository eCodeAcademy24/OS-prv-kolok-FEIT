#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t childVowels, childConsonants;
    char array[1000];
    char character;
    int vowels = 0;
    int consonants = 0;
    int characters = 0;
    int vowelsFinished = 0;
    int consonantsFinished = 0;
    int i, check;

    FILE* file;

    if (argc < 2) {
        printf("Invalid number of arguments sent to the command line!\n");
        exit(-1);
    }

    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Error wile opening the file for reading\n");
        exit(-1);
    }

    while ((character = getc(file)) != EOF) {
        array[characters] = character;
        ++characters;
    }

    childVowels = fork();

    if (childVowels > 0) {
        childConsonants = fork();

        if (childConsonants == 0) {
            for (i = 0; i < characters; ++i) {
                if (isalpha(array[i])) {
                    check = (array[i] == 'A' || array[i] == 'E' || array[i] == 'I' || array[i] == 'O' || array[i] == 'U' ||
                             array[i] == 'a' || array[i] == 'e' || array[i] == 'i' || array[i] == 'o' || array[i] == 'u');

                    if (check == 0) {
                        ++consonants;
                    }
                }
            }

            printf("There are %d consonants in the file\n", consonants);
        }
        else {
            while (vowelsFinished != 1 && consonantsFinished != 1) {
                if (waitpid(childVowels, NULL, WNOHANG) == childVowels) {
                    vowelsFinished = 1;
                }

                if (waitpid(childConsonants, NULL, WNOHANG) == childConsonants) {
                    consonantsFinished = 1;
                }
            }
        }
    }
    else {
        for (i = 0; i < characters; ++i) {
            if (isalpha(array[i])) {
                check = (array[i] == 'A' || array[i] == 'E' || array[i] == 'I' || array[i] == 'O' || array[i] == 'U' ||
                         array[i] == 'a' || array[i] == 'e' || array[i] == 'i' || array[i] == 'o' || array[i] == 'u');

                if (check == 1) {
                    ++vowels;
                }
            }
        }

        printf("There are %d vowels in the file\n", vowels);
    }

    return 0;
}