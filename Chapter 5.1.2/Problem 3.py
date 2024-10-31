#!/usr/bin/python3
import sys, os

if len(sys.argv) < 2:
    print("Invalid number of arguments sent to the command line!")
else:
    files = sys.argv[1:]
    currency = ["$", "€", "£", "CHF"]
    foundCurrency = []

    for file in files:
        if os.path.exists(file):
            inFile = open(file, "r")
            currencyValues = dict()

            for lines in inFile:
                words = lines.split(' ')

                if words[0] in currency:
                    if words[0] not in foundCurrency:
                        foundCurrency.append(words[0])

                    if words[0] not in currencyValues:
                        currencyValues[words[0]] = int(words[1])
                    else:
                        currencyValues[words[0]] = currencyValues[words[0]] + int(words[1])

            total = 0

            for key in currencyValues:
                value = input("Please enter the value of the following currency {}\n".format(key))
                total = total + int(value) * currencyValues[key]

            print("The total amount of value inside the file is", total)
        else:
            print("Some of the files are missing, cannot execute Python script")

    print("The Python script found the following currencies in the files", foundCurrency)