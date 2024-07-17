// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Creating a global variable to keep a track of words count
unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Obtaining the hash value of the word
    unsigned int hash_value = hash(word);

    // Access the linked list at the hash value obtained
    node *cursor = table[hash_value];

    // Traverse till you find the word in the linked list at the obtained hash value
    while (cursor != NULL)
    {
        // If found the word return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash_value = 0;

    // Looping until the null terminator '\0'
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Making sure if characters are letters only
        if (isalpha(word[i]))
        {
            // Making sure letters are case insensitive
            // Adding the jash values
            hash_value += toupper(word[i]) - 'A';
        }
    }

    // Ensuring hash_value is within the range from 0 to N-1
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file.
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char buffer[LENGTH+1];

    // Reading each word in the file
    while (fscanf(source, "%45s", buffer) != EOF)
    {
        // Creating a new node
        node *new_node = malloc(sizeof(node));

        // Closing the file if the new node is null
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, buffer);

        // Indexing the Hash word
        unsigned int index = hash(buffer);

        // Inserting the new node into the hash table
        new_node -> next = table[index];
        table[index] = new_node;

        // Keeping the track of size
        word_count++;

    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //TODO
    // returns the words loaded in dictionary that we counted in load function
    return word_count;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Iterating over each bucket
    for (int i = 0; i < N; i++)
    {
         // Assigning cursor to keep track of nodes
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    return true;
}
