// write a program that enables you to encrypt messages using Caesar’s cipher.
// At the time the user executes the program, they should decide, by providing a 
// command-line argument, what the key should be in the secret message 
// they’ll provide at runtime. We shouldn’t necessarily assume that the user’s key
// is going to be a number; though you may assume that, if it is a number, it will 
// be a positive integer.

#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool only_digits(string s);
string rotate(string plaintext, int key);

int main(int argc, string argv[])
{
    // Checking the command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate that the argument contains only digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converting the argv to an integer
    int key  = atoi(argv[1]);

    // Prompt the user for the text
    string plaintext = get_string("plaintext: ");
    string ciphertext = rotate(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

string rotate(string plaintext, int key)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            char base;
            if (isupper(c))
            {
                base = 'A';
            }
            else
            {
                base = 'a';
            }

            int index = (c - base + key) % 26;
            char encrypted_char = index + base;
            printf("%c", encrypted_char);
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}


