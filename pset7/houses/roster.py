from cs50 import SQL
import sys
import csv
import os

# capure the arguments passed by comand line
argumentsCount = len(sys.argv)

# make connection with DB
db = SQL("sqlite:///students.db")

# allow usage only if one argument was passed
if argumentsCount != 2:
    print('Should use "roster.py house"')
    exit()

house = sys.argv[1]

# retrieve data from students table
students = db.execute("""
    SELECT
        *
    FROM
        students
    WHERE
        house = :house
    ORDER BY
        last ASC,
        first ASC
    """, house=house)
    
# print each row retrieved
for row in students:
    if row["middle"] != None:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))