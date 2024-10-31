#!/usr/bin/python3
import sys, os

if len(sys.argv) < 3:
    print("Invalid number of arguments sent to the command line!")
else:
    files = sys.argv[1:]
    fileAmount = len(sys.argv) - 1
    i = 0

    commonHashtags = dict()

    while i < fileAmount:
        firstFile = files[i]
        i = i + 1
        secondFile = files[i]

        if os.path.exists(firstFile) and os.path.exists(secondFile):
            inFirstFile = open(firstFile, "r")
            inSecondFile = open(secondFile, "r")

            firstHashtags = []
            secondHashtags = []

            for line in inFirstFile:
                words = line.split(' ')

                for word in words:
                    if len(word) > 1:
                        if '#' == word[0]:
                            firstHashtags.append(word.replace('\n', ''))

            for line in inSecondFile:
                words = line.split(' ')

                for word in words:
                    if len(word) > 1:
                        if '#' == word[0]:
                            secondHashtags.append(word.replace('\n', ''))

            outputFile = firstFile.replace(".txt", "")
            outputFile = outputFile + secondFile

            outFile = open(outputFile, "w")
            count = 0

            if len(firstHashtags) <= len(secondHashtags):
                for firstHashtag in firstHashtags:
                    for secondHashtag in secondHashtags:
                        if firstHashtag == secondHashtag:
                            outFile.write("{}\n".format(firstHashtag))
                            count = count + 1

                        if secondHashtag not in commonHashtags:
                            commonHashtags[secondHashtag] = 1
                        else:
                            commonHashtags[secondHashtag] = commonHashtags[secondHashtag] + 1
                    
                    if firstHashtag not in commonHashtags:
                        commonHashtags[firstHashtag] = 1
                    else:
                        commonHashtags[firstHashtag] = commonHashtags[firstHashtag] + 1
            else:
                for secondHashtag in secondHashtags:
                    for firstHashtag in firstHashtags:
                        if secondHashtag == firstHashtag:
                            outFile.write("{}\n".format(secondHashtag))
                            count = count + 1

                        if firstHashtag not in commonHashtags:
                            commonHashtags[firstHashtag] = 1
                        else:
                            commonHashtags[firstHashtag] = commonHashtags[firstHashtag] + 1
                    
                    if secondHashtag not in commonHashtags:
                        commonHashtags[secondHashtag] = 1
                    else:
                        commonHashtags[secondHashtag] = commonHashtags[secondHashtag] + 1

            outFile.write("There were {} hashtags which were the same\n".format(count))

            if i + 2 >= fileAmount:
                break
        else:
            print("Some of the files are missing, cannot execute Python script")
        
        i = i + 1
    
    maximum = 0
    commonHashtag = ''

    for hashtag in commonHashtags:
        if commonHashtags[hashtag] > maximum:
            maximum = commonHashtags[hashtag]
            commonHashtag = hashtag

    print("The most common hashtag in all of the files is {}".format(commonHashtag))