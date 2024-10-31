#!/usr/bin/python3
import sys, os

if len(sys.argv) != 4:
    print("Invalid number of arguments sent on the command line, please try again!")
else:
    firstFile = sys.argv[1]
    secondFile = sys.argv[2]
    outputFile = sys.argv[3]

    if os.path.exists(firstFile) and os.path.exists(secondFile) and os.path.exists(outputFile):
        inFirstFile = open(firstFile, "r")
        inSecondFile = open(secondFile, "r")
        outFile = open(outputFile, "w")

        firstFileLines = inFirstFile.readlines()
        secondFileLines = inSecondFile.readlines()

        rangeIndex = (len(firstFileLines), True) if len(firstFileLines) <= len(secondFileLines) else (len(secondFileLines), False)
        index = 0

        for i in range(rangeIndex[0]):
            firstFileLine = firstFileLines[i]
            secondFileLine = secondFileLines[i]

            print("New line from the first file:", firstFileLine)
            outFile.write(firstFileLine)

            print("New line from the second file:", secondFileLine)
            outFile.write(secondFileLine)

            index = i

        if not rangeIndex[1]:
            for i in range(index + 1, len(firstFileLines)):
                firstFileLine = firstFileLines[i]

                print("New line from the first file:", firstFileLine)
                outFile.write(firstFileLine)
        else:
            for i in range(index + 1, len(secondFileLines)):
                secondFileLine = secondFileLines[i]

                print("New line from the second file:", secondFileLine)
                outFile.write(secondFileLine)

        inFirstFile.close()
        inSecondFile.close()
        outFile.close()
    else:
        print("One of the files does not exist, please try again!")