# TODO
from cs50 import SQL
import sys
import csv
import os


argumentsCount = len(sys.argv)

# conncetion to DB
db = SQL("sqlite:///students.db")

# uncoment if need clear row
# db.execute("DELETE FROM students WHERE 1=1")

# allow usage only passing one argument
if argumentsCount != 2:
    print('Should use "import.py file.csv"')
    exit()


# open csv file
with open(sys.argv[1], newline='') as csvDatabase:
    # variable to build the data that will be put on DB
    data = []
    database = csv.reader(csvDatabase, delimiter=',')
    # skip fisrt row (header)
    next(database)
    # build data
    for row in database:
        rowData = []
        name = row[0].split(" ")
        rowData.append(name[0])
        # if has middle name ? append it : append None 
        rowData.append(name[1]) if len(name) == 3 else rowData.append(None) 
        # if has middle name ? append third positon of name : append second position
        rowData.append(name[1]) if len(name) == 2 else rowData.append(name[2])
        rowData.append(row[1])
        rowData.append(row[2])
        data.append(rowData)

# insert each row of data
for row in data:
    print(row)
    db.execute(
        "INSERT INTO students (first, middle, last, house, birth) VALUES (:first, :middle, :last, :house, :birth)", 
        first=row[0], middle=row[1], last=row[2], house=row[3], birth=row[4]
    )