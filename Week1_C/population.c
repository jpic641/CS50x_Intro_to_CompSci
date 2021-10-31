#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int start_Size, end_Size, count = 0;
    int current_Size;

    // Prompt for start size
    do
    {
        start_Size = get_int("Start size: ");
    }
    while (start_Size < 9);

    // Prompt for end size
    do
    {
        end_Size = get_int("End size: ");
    }
    while (start_Size > end_Size);

    // Set current size to start size
    current_Size = start_Size;

    // Calculate number of years until we reach threshold
    while (current_Size < end_Size)
    {
        count++;
        current_Size = current_Size + (current_Size / 3) - (current_Size / 4);
    }

    // Print number of years
    printf("Years: %i\n", count);

}

