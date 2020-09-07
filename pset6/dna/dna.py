import csv
import sys
import os

#################################################################

# function that receive a STR  and a sequence as parameters em return a de max reapet successively
# for each position test if the slice is equal the STR
#   if yes -> incremente a counter and test the next fragment
#   if no -> test if the last repeat sucessively is greater than max
#       if yes -> update max repeat and reset repeat counter
#       if no -> only reset repeat counter


def countSTR(STR, sequence):
    repeatSTR = 0
    maxRepeat = 0
    lenSTR = len(STR)
    lenSequence = len(sequence)
    i = 0
    while i < lenSequence:
        # print(f'STR: {STR} lenSTR: {lenSTR} teste: {sequence[i:i+lenSTR]} ')
        
        if sequence[i:i+lenSTR] == STR:
            repeatSTR += 1
            i += lenSTR
            # print(repeatSTR)
            # print('somou')
        else:
            if repeatSTR > maxRepeat:
                maxRepeat = repeatSTR
            else:
                repeatSTR = 0
                # print("trocou")
            i += 1
    # return the max repeats
    return maxRepeat
#################################################################
# function to open sequence file, get the first row as string ans return it


def getSequence(sequencePath):
    with open(sequencePath, newline='') as csvSequence:
        sequence = csv.reader(csvSequence, delimiter=' ')
        for row in sequence:
            # print(row[0])
            return row[0]
#################################################################    
# main function that open database file informed at argv and call function to check maxrepeat of each STR of database then look for
# who match with the result


def main():
    if not len(sys.argv) == 3:
        print("Usage: python dna.py data.csv sequence.txt")
    else:
        sequencePath = sys.argv[2]
        with open(sys.argv[1], newline='') as csvDatabase:
            sequenceResult = []
            database = csv.reader(csvDatabase, delimiter=' ', quotechar=',')
            
            for row in database:
                row = row[0].split(",")
                for i in row[1:]:
                    # print(i)
                    sequenceResult.append((countSTR(i, getSequence(sequencePath))))
                break
            # print(sequenceResult)
            for row in database:
                row = row[0].split(",")
                STRMatchCounter = 0
                for i in range(len(sequenceResult)):
                    # print(f'sq:{sequenceResult[i]} row[i]:{row[i+1]}')
                    if int(sequenceResult[i]) == int(row[i+1]):
                        STRMatchCounter += 1
                if STRMatchCounter == len(sequenceResult):
                    return(row[0])
            return ("No match")


try:
    print(main())
except:
    print("Usage: python dna.py data.csv sequence.txt")
