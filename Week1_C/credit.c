#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int checksum(long cardNum, int nDigLen);
long get_Digit(long cardNum, int n);
string check_Card(long cardNum, int nDigits);

int main(void)
{
    // Create an output buffer to store card as str
    char sDigits[50];

    // Prompt user for card number
    long n = get_long("Number: ");

    // Convert card number to string annd count digits
    sprintf(sDigits, "%li", n);
    int nDigits = strlen(sDigits);

    // Check the sum
    int card_Sum = checksum(n, nDigits);

    // Check the card
    if (card_Sum % 10 == 0)
    {
        string output = check_Card(n, nDigits);
        printf("%s", output);
    }
    else
    {
        printf("INVALID\n");
    }

}



int checksum(long cardNum, int nDigLen)
{
    long digit;
    int i, j;
    int sum1 = 0;
    int sum2 = 0;
    int sumT = 0;


    // Loop through every second digit from 2nd last
    for (i = 1; i < nDigLen + 1; i = i + 2)
    {
        // Get digit at i-th position and multiply by 2
        digit = get_Digit(cardNum, i);
        digit *= 2;

        // Check if doubled digit results in a double digit (i.e. 10)
        if (digit > 9)
        {
            // Since the highest number can be 18, assume first digit
            // is 1 and the second digit the modulus of 10
            digit = 1 + (digit % 10);
        }

        sum1 += digit;

    }

    // Loop through the digits that weren't doubled
    for (j = 0; j < nDigLen + 1; j = j + 2)
    {
        // Get digit at j-th position and sum up total
        digit = get_Digit(cardNum, j);
        sum2 += digit;
    }


    sumT = sum1 + sum2;
    //printf("%i", sumT);

    return (sumT);

}

// Returns n-th digit of card num
long get_Digit(long cardNum, int n)
{
    long r;

    r = cardNum / pow(10, n);
    r = r % 10;

    return r;
}

string check_Card(long cardNum, int nDigits)
{
    long first_Digit = get_Digit(cardNum, nDigits - 1);
    long second_Digit = get_Digit(cardNum, nDigits - 2);


    // Check if card is AMEX
    if ((nDigits == 15) && (first_Digit == 3))
    {
        if ((second_Digit == 4) || (second_Digit == 7))
        {
            return ("AMEX\n");
        }
    }

    // Check if card is VISA
    else if (((nDigits == 13) || (nDigits == 16)) && (first_Digit == 4))
    {
        return ("VISA\n");
    }

    // Check if card is MASTERCARD
    else if ((nDigits == 16) && (first_Digit == 5))
    {
        if ((second_Digit > 0) && (second_Digit < 6))
        {
            return ("MASTERCARD\n");
        }
    }

    // If none are met, card is invalid
    return ("INVALID\n");

}