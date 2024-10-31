#!/usr/bin/python3
import sys, os, re

if len(sys.argv) < 2:
    print("No arguments send on the command line, please try again!")
else:
    for i in range(1, len(sys.argv)):
        inputFile = sys.argv[i]
        outputFile = sys.argv[i].replace(".txt", "-Out.txt")

        if os.path.exists(inputFile):
            inFile = open(inputFile, "r")
            outFile = open(outputFile, "w")
            index = 0

            for line in inFile:
                if index == 0:
                    print("The first line of file {} is: {}".format(inputFile, line))
                    index = index + 1
                
                newLine = re.sub("\.$", "!", line)
                outFile.write(newLine)
            
            inFile.close()
            outFile.close()
        else:
            print("The file doesn't exist!")