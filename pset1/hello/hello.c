#include <stdio.h>
#include <cs50.h>

//main function
int main(void)
{
    //get the user name
    string name = get_string("What is your name?\n");
    //say hello to username
    printf("hello, %s\n", name);
}