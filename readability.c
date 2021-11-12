#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// PROTOTYPE
float compute_grade(string text);
int count_letters(string text1);
int count_words(string text2);
int count_sentences(string text3);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    int grade = compute_grade(text);
    //printf("%i", grade);

    // Print out grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((grade >= 1) && (grade <= 16))
    {
        printf("Grade %i\n", grade);
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }

}


float compute_grade(string text)
{
    // Initialize variables
    float index = 0.0;
    float l_avg, s_avg;

    // Compute the Coleman-Liau incex for text
    // Count letters
    int l = count_letters(text);
    //printf("%i letter(s)\n", l);

    // Count words
    int w = count_words(text);
    //printf("%i word(s)\n", w);

    // Count sentences
    int sen = count_sentences(text);
    //printf("%i sentence(s)\n", sen);

    //Compute average letters/sen per 100 words
    l_avg = l / (w / 100.0);
    //printf("%f\n", l_avg);
    s_avg = sen / (w / 100.0);
    //printf("%f\n", s_avg);

    index = round((0.0588 * l_avg) - (0.296 * s_avg) - 15.8);

    return index;
}

int count_letters(string text1)
{
    // Init variables
    int letters = 0;

    // Find where
    for (int i = 0, n = strlen(text1); i < n; i++)
    {
        // If char is in the alphabet, add to count
        if (isalpha(text1[i]))
        {
            letters += 1;
        }
    }

    return letters;
}

int count_words(string text2)
{
    // Initialize variables
    int words = 0;

    for (int j = 0, n1 = strlen(text2); j < n1; j++)
    {
        //If char is a space or last charactor of sentence, add count to words
        if ((isspace(text2[j])) || (j == n1 - 1))
        {
            words += 1;
        }
    }

    return words;
}

int count_sentences(string text3)
{
    // Init var
    int sentences = 0;

    for (int k = 0, n2 = strlen(text3); k < n2; k++)
    {
        // If char is . or ! or ?, then count as a sentence
        if ((text3[k] == '.') || (text3[k] == '!') || (text3[k] == '?'))
        {
            sentences += 1;
        }
    }

    return sentences;
}