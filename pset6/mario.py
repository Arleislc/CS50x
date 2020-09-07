# define a variable n
Height = ""

# acept only numbers between 1 and 8
while (not((Height.isnumeric() and int(Height) > 0 and int(Height) < 9))):
    Height = input("Height: ")

# print lines
for i in range(1, int(Height)+1):
    print((int(Height)-i)*" " + i*"#" + "  " + i*"#")