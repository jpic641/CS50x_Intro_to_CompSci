#include <stdio.h>
#include <cs50.h>

void pyramid(int h);
void char_Repeat(int c, string s);

int main(void)
{
    // Initialize variables
    int height;

    // Prompt user for a number between 1-8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print pyramid
    pyramid(height);
}

void pyramid(int h)
{
    int spaces, i;

    // Loop over the each level of the pyramid
    for (i = 0; i < h; i++)
    {
        // Calc how many spaces are required and print
        spaces = h - i - 1;

        // Print spaces eqv. to h - 1
        printf("%*s", spaces, "");

        // Repeat hashes for pyramid block
        char_Repeat(i + 1, "#");

        // Print center spacing
        printf("%*s", 2, "");

        // Print other side of pyramid
        char_Repeat(i + 1, "#");
        printf("\n");

    }

}

void char_Repeat(int c, string s)
{
    // Print hashes and spacing between
    for (int j = 0; j < c; j++)
    {
        printf("%s", s);
    }
}