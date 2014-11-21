
#include "hashTable.h"

table_node hash_table[TABLE_LENGTH];


//TODO: Error checking
void key_hash_t( ) 
{
	char key = 'a';
	for ( int i = 0; i < TABLE_LENGTH; i++ )
	{
		hash_table[i].letter = (key + i);
	}
}

//TODO: return and error checking 'WILL THIS MAKE AN EXTRA NODE'
bool load_hash_t(char *file_name)
{
	char word[WORD_LENGTH];
	char c;
	int index = 0, hash_val = 0, size = get_file_size(file_name);
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL)
	{
		printf ("File not found...\n");
		exit(1);
	}

	for (int word_count = 0; word_count < size; word_count++) 
	{
		node *new_node = malloc( sizeof(*new_node) ); 

		// make sure malloc was successful
		if (new_node == NULL)
		{
			printf ("Failed to allocate memory...\n");
			exit(1);
		}

		new_node->next = NULL;
		
		while ((c = fgetc(file)) != '\n')
		{
			word[index] = c;
			index++;
		}

		hash_val = hash(word);         

		for (int j = 0; j < index; j++)
		{
			new_node->word[j] = word[j];
		}

		index = 0;

		// if this bucket has no nodes yet add it here
		if (hash_table[hash_val].next == NULL)
		{
			hash_table[hash_val].next = new_node;
		}
		else
		{
			//add new  node to end of list
			new_node->next = hash_table[hash_val].next;
			hash_table[hash_val].next = new_node;
		}
	}
	fclose(file);
	return true;
}

// TODO: return && error checking
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

//TODO: error checking
int get_file_size(char *file_name)
{
	char c;
	int line_count = 0;
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL)
	{
		printf("File not found..\n");
		return 1;
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

//TODO: error checking
int hash(char *str)
{
	if (str == NULL)
	{
		printf("NULL pointer..\n");
		return 1;
	}
	return (tolower(str[0]) - 97);
}

bool check(const char* word)
{
	/**
	 * loop threw array to find bucket
	 * traverse list to find word
	 * return true if found false if not
	 */
	return true;
}

 //TODO: error checking "check if bucket is empty", return 0 if not loaded
unsigned int size( )
{
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