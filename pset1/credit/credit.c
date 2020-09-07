#include <stdio.h>
#include <cs50.h>

//percorrer os numeros do cartão de crédito
//1 - se a posição do dígito for par > multiplica por 2
//2 - se a posição do digito for impar > soma
//3 - somar os
//pegar o último digito da soma


    long cc_number = get_long("Number: ");

    int last_digits = 0;
    int nDigits = 1;
    int total = 0;
    int begining_digits = 0;

    while (cc_number != 0)
    {

        int digit = cc_number % 10;
        begining_digits = (digit * 100 + begining_digits) / 10;
        cc_number = cc_number / 10;
        //printf("%li %i %i\n",cc_number,nDigits, digit);

        //printf("%i\n",nDigits % 2 == 0);
        if (nDigits % 2 == 0)
        {
            //se o resultado do digito vezes 2 for maior que 9
            int digit2 = digit * 2;
            if (digit2 > 9)
            {
                //soma os digitos
                total = total + digit2 % 10 + digit2 / 10;
                //printf("digit2 %% 10 = %i;digit/10 = %i\n",digit2 % 10,digit2 / 10);
            }
            else
            {
                total = total + digit2;
            }
        }
        else
        {
            //soma
            total = total + digit;
        }


        nDigits = nDigits + 1;
    }

    nDigits--;
    
    //printf("total= %i -- begining_digits= %i -- nDigits= %i\n",total%10,begining_digits,nDigits);
    if (total % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if ((nDigits == 15 && begining_digits == 34) || begining_digits == 37)
        {
            printf("AMEX\n");
        }
        else if (nDigits == 16 && (begining_digits >= 51 && begining_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((nDigits == 13 || nDigits == 16)  && (begining_digits >= 40 && begining_digits <= 49))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

}

