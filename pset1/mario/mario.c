#include <stdio.h>
#include <cs50.h>

//print the left hashs
void print_hashs_left(int n, int max)

{
    for (int i = 1; i <= max; i++)
    {
        if (i < max - n)
        {
            printf(" ");
        } 
        else 
        {
            printf("#");
        }
    }
}

//print the right hashs
void print_hashs_right(int n)
{
    for (int i = 1; i <= n + 1; i++)
    {
        printf("#");
    }
}

//print the line
void print_line(int n, int max)
{
    print_hashs_left(n, max);
    printf("  ");
    print_hashs_right(n);
    printf("\n");
}

//construct the pyramid
void pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        //construct a line
        print_line(i, n);
    }
}

//main function
int main(void)
{
    int n = 0;
    //make the user pass an acceptable value
    do 
    {
        //get the height of the pyramid
        n = get_int("Height: ");
    } 
    while (n < 1 || n > 8);
    //calls the pyramid function
    pyramid(n);
}