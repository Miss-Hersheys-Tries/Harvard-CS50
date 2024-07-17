// , create a program that enables you to encrypt messages using a substitution cipher.
// At the time the user executes the program, they should decide, by providing a command-line
// argument, on what the key should be in the secret message they’ll provide at runtime.

#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool only_alpha(string s);
bool diff_char(string s);
void substitute(string plaintext, string key);

int main(int argc, string argv[])
{
    // Checking the command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check for key length
    int n = strlen(argv[1]);
    if ( n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for non-alphabetic characters
    if (!only_alpha(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    // Check for repeated characters (case-sensitive)
    if (!diff_char(argv[1]))
    {
        printf("Key must contain unique characters\n");
        return 1;
    }

    string key = argv[1];

    // Prompt the user for the text
    string plaintext = get_string("plaintext: ");

    // Calls the substitue function to encrypt and print the text
    substitute(plaintext, key);

    return 0;
}

bool only_alpha(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool diff_char(string s)
{
    bool char_seen[26] = {false};
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = tolower(s[i]);
        int index = c - 'a';
        if (char_seen[index])
        {
            return false;
        }
        char_seen[index] = true;
    }
    return true;
}

void substitute(string plaintext, string key)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            char encrypted_char;
            if (isupper(c))
            {
                encrypted_char = toupper(key[c - 'A']);
            }
            else
            {
                encrypted_char = tolower(key[c - 'a']);
            }
            printf("%c", encrypted_char);
        }

        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}

