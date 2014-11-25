
#include "hashTable.h"
#include <stdbool.h>


table_node hash_table[TABLE_LENGTH];

bool loaded = true;

//assigning letters a-z to table nodes for buckets
void key_hash_t( ) 
{
	char key = 'a';
	for ( int i = 0; i < TABLE_LENGTH; i++ )
	{
		hash_table[i].letter = (key + i);
	}
}

/*TODO: 
 * I think this 'WILL THIS MAKE AN EXTRA NODE'
 *
 * 
 **/
bool load_hash_t(const char *file_name)
{
	char word[WORD_LENGTH];
	char c;
	int index = 0, hash_val = 0, size = get_file_size(file_name);
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL)
	{
		printf ("File not found...\n");
		return false;
	}

	for (int word_count = 0; word_count < size; word_count++) 
	{
		node *new_node = malloc( sizeof(*new_node) ); 

		// make sure malloc was successful
		if (new_node == NULL)
		{
			printf ("Failed to allocate memory...\n");
			return false;
		}

		new_node->next = NULL;
		
		//read word from file
		while ((c = fgetc(file)) != '\n')
		{
			word[index] = c;
			index++;
		}
		
		//terminate string
		word[index] ='\0';
		
		//hash word
		hash_val = hash(word);
	
		//copy string into node
		strcpy(new_node->word, word);
	
		//reset index
		index = 0;

		//add new  node to list
		new_node->next = hash_table[hash_val].next;
		hash_table[hash_val].next = new_node;
	}
	fclose(file);
	return true;
}

/**
 * Free all nodes created
 * in load_hash_t
 **/
bool unload_hash_t( )
{
	/**
	 * loop through array
	 * traverse each list and
	 * delete each node
	 **/
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		node *cursor = hash_table[i].next;

		while (cursor != NULL)
		{
			node *temp = cursor;
			cursor = cursor->next;
			free(temp);
		}
	}
	return true;
}

/**
 * get size of dictionary file 
 * for load function
 * */
int get_file_size(const char *file_name)
{
	char c;
	int line_count = 0;
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL)
	{
		printf("File not found..\n");
		exit(EXIT_FAILURE);
	}

	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			line_count++;
		}
	}
	fclose(file);

	return line_count;
}

/**
 * convert first char to lowercase
 * subtract by 97 to give correct 
 * array index
 **/
int hash(const char *str)
{
	if (str == NULL)
	{
		printf("NULL pointer..\n");
		exit(EXIT_FAILURE);
	}
	return (tolower(str[0]) - 97);
}

/**
 * loop threw array to find bucket
 * traverse list to find word
 * return true if found false if not
 */
bool check(const char* word)
{
	//hash word
	int hash_val = hash(word); 

	//must reassign to make editable
	char *eword = strdup(word);

	//convert word to lower
	word_tolower(eword);

	node *cursor = NULL;
	
	//iterate table array to find bucket
	for (int i = 0; i  < TABLE_LENGTH; i ++)
	{
		cursor = hash_table[hash_val].next;

		//traverse list for bucket hash_val
		while (cursor != NULL)
		{
			if (strcmp(eword, cursor->word) == 0)
			{
				free(eword);
				return true;
			}
			else
			{
				cursor = cursor->next;
			}
		}
	}
	free(eword);
	return false;
}

/**
 * iterate through array and
 * traverse each list counting each node
 * as I go by
 **/
unsigned int size( )
{
	if (!loaded)
	{
		printf("Dictionary not loaded..\n");
		return 0;
	}
	node *cursor = NULL;
	int node_count = 0;
		
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		cursor = hash_table[i].next;
		while (cursor != NULL)
		{
			node_count++;
			cursor = cursor->next;
		}
	}
	return node_count;
}

/**
 *Convert all chars in word
 *to lowercase to compare
 *to strings in dict file 
 **/
void word_tolower(char* word)
{
	if (word == NULL)
	{
		printf("NULL pointer ...\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0, length = strlen(word); i  < length; i ++)
	{
		word[i] = tolower(word[i]);
	}
}