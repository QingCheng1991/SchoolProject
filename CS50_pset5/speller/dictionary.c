/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

 typedef struct node
    {
        char word[LENGTH +1];
        struct node *next;
    }
 node;
    
    
    
     node* hashtable[HASHTABLE_SIZE];
    
    int word_count=0;

// the hash function from the internet resources    
int hashing_function(char *word){
    unsigned int sum=0;
    for (int i=0;word[i] != '\0';i++)
    {
        sum += word[i];
        
    }   
    return sum % HASHTABLE_SIZE;
}
    
    

    
    
    

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
 // TODO
    // creates a temp variable that stores a lower-cased version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    
    // find what index of the array the word should be in
    int index = hashing_function(temp);
    
    // if hashtable is empty at index, return false
    if (hashtable[index] == NULL)
    {
        return false;
    }
    
    // create cursor to compare to word
    node* cursor = hashtable[index];
    
    // if hashtable is not empty at index, iterate through words and compare
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    // if you don't find the word, return false
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *fp=fopen(dictionary, "r");
    if(fp==NULL)
    {
        printf("the file does not exist\n");
        return false;
    }
    
    char buffer[LENGTH+2];
    
    while(fscanf(fp,"%s",buffer)!= EOF)
    {
     
     node * new_node =malloc(sizeof(node)); 
     if(new_node == NULL)
     {
         printf("can create new space\n");
         unload();
         
         return false;
     }
     word_count++;
     
     strcpy(new_node->word,buffer);
     new_node->next=NULL;
     int hash = hashing_function(buffer);
     
     if (hashtable[hash] == NULL)
        {
            hashtable[hash] = new_node;
            new_node->next = NULL;
        }
        
        // if hashtable is not empty at index, append
        else
        {
            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;
        }      
    
    }

   
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
 // TODO
    // if dictionary is loaded, return number of words
    if (word_count > 0)
    {
        return word_count;
    }
     
    // if dictionary hasn't been loaded, return 0
    else
        return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
   // TODO
    // create a variable to go through index
    int index = 0;
    
    // iterate through entire hashtable array
    while (index < HASHTABLE_SIZE)
    {
        // if hashtable is empty at index, go to next index
        if (hashtable[index] == NULL)
        {
            index++;
        }
        
        // if hashtable is not empty, iterate through nodes and start freeing
        else
        {
            while(hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }
            
            // once hashtable is empty at index, go to next index
            index++;
        }
    }
    
    // return true if successful
    return true;
}
