
# percorrer os numeros do cartão de crédito
# 1 - se a posição do dígito for par > multiplica por 2
# 2 - se a posição do digito for impar > soma
# 3 - somar os
# pegar o último digito da soma


cc_number = input("Number: ")
inverted_cc_number = cc_number[::-1]

product = ""
sumProduct = 0
sumOthers = 0
for i in range(len(inverted_cc_number)):
    if i % 2 != 0:
        product += str(int(inverted_cc_number[i])*2)
    else:
        sumOthers += int(inverted_cc_number[i])
for i in product:
    sumProduct += int(i)


isValid = (sumProduct+sumOthers) % 10 == 0

if isValid:
    if(int(cc_number[:2]) == 34 or int(cc_number[:2]) == 37):
        print("AMEX")
    elif(int(cc_number[:2]) >= 51 and int(cc_number[:2]) <= 55):
        print("MASTERCARD")
    elif int(cc_number[:1]) == 4:
        print("VISA")
else:
    print("INVALID")