#!/usr/bin/python3
import sys

if len(sys.argv) < 3:
    print("Invalid number of arguments send on the command line, please try again!")
else:
    employees = sys.argv[1:]
    indexRange = int(len(employees) / 2)

    for index in range(indexRange):
        employee = employees[index]
        substitute = employees[-(index + 1)]

        if employee != substitute:
            employees[index] = substitute
            employees[-(index + 1)] = employee
    
    print("The employees of the company are:", employees)