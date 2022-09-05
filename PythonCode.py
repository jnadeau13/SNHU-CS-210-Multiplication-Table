''' Jen Nadeau
    CS 210 
    Module Six Assignment: Integrating Languages
    6/11/2022
    PythonCode.py
'''

import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# Python function to display muliplication table based on input
def MultiplicationTable(x):
    print()

    for i in range(1, 11):
        print (str(x) + " X " + str(i) + " = " + str(x * i))

    print("\nMuliplication Table for:")

    return x

# Python function to display input value doubled 
def DoubleValue(x):
    print()
    return x * 2