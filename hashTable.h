#ifndef HASHTABLE
#define HASHTABLE

#define WORD_LENGTH  45
#define TABLE_LENGTH 26

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

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

int get_file_size(const char *file);

void key_hash_t(const char *file); 

bool load_hash_t(const char *file);

bool unload_hash_t( );

int hash(const char *str);

unsigned int size( );

bool check(const char* word);

void word_tolower(char *word);

#endif