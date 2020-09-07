#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{


    //atoi convert a string to a number
    //strlen(text) to know the length of the text

    //A->Z = 65->90
    //a->z = 97->122

    //convert ASCII to alphabetical index
    //shift alphabetical index using  formula
    //convert result cask to ASCII (preserve de case)

    //allow to use onlye ./caesar key
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    
    //allow only valid integer
    for (int i = 0 ; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("%c", argv[1][i]);
            printf("Key must be a valid number\n");
            return 1;
        }
    }
    
    
    //TODO
    //GET KEY
    string text = argv[1];
    //Get plaintext
    string plainText = get_string("Text: ");
    //Enchiper
    int key = atoi(argv[1]);
  
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plainText); i++)
    {
        if (isalpha(plainText[i]))
        {
            if (isupper(plainText[i]))
            {
                char m = 'A';
                printf("%c", (plainText[i] - m + key) % 26 + m);
            } 
            else
            {
                char m = 'a';
                printf("%c", (plainText[i] - m + key) % 26 + m);
            }
        }
        else
        {
            printf("%c", plainText[i]);
        }
    }
    printf("\n");
}
    
        
    
