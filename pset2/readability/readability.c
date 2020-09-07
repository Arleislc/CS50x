
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


int main(void)
{
    //ask a text to the user
    string text = get_string("Text: ");

    //number of letters, words and sentences in the text
    //   number of letters = summ of any charcter between a and z or A and Z
    int nLetters = 0;
    //   number of words = sum of sequences of characters separeted by space
    int nWords = 1;
    //   number of sentences = sum of "!, ? or ."
    int nSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            //letter
            nLetters++;
        }
        else if (text[i] == 32)
        {
            //words
            nWords++;
        } 
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            //sentences
            nSentences++;
        }
    }



    float const L = (float) nLetters / (float) nWords * 100;
    float const S = (float) nSentences / (float) nWords * 100;
    float  index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);

    //print grade (int)
    //   if grade >= 16 print Grade 16+
    //   if grade <1 print Grade 1

    //printf("nLetters= %i\n", nLetters);
    //printf("nWords= %i\n", nWords);
    //printf("nSentences= %i\n", nSentences);


    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }


}


