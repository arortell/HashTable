#ifndef HASHTABLE
#define HASHTABLE

#define WORD_LENGTH  45
#define TABLE_LENGTH 26

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


//struct used to hold each word
typedef struct node 
{
    char word[WORD_LENGTH + 1];
    struct node *next;
	
} node;

// table 
typedef struct table_node 
{
    char letter;
    struct node *next;
	
} table_node;

//TODO: FILE needs to be char*
int get_file_size(char *file);

void key_hash_t(char *file); 

bool load_hash_t(char *file);

bool unload_hash_t( );

int hash(char *str);

unsigned int size( );

bool check(const char* word);

#endif