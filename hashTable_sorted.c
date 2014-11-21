
#include "hashTable.h"

table_node hash_table[TABLE_LENGTH];

// TODO: Return type, error checking
int create_hash_t( )
{
	for ( int i = 0; i < TABLE_LENGTH; i++ )
	{
		hash_table[i].next = malloc( sizeof( *hash_table[i].next ) );

		if ( hash_table[i].next == NULL )
		{ 
			return 1;
		}
	}
	return 0;
}

//TODO: Error checking
void key_hash_t( ) 
{
	char key = 'a';
	for ( int i = 0; i < TABLE_LENGTH; i++ )
	{
		hash_table[i].letter = (key + i);
	}
}

//TODO: 
bool load_hash_t(FILE *file)
{
	char word[WORD_LENGTH];
	char c;
	int index = 0, hash_val = 0;
	int size = get_file_size(file);
	file = fopen("large", "r");
	
	if (file == NULL)
	{
		printf ("File not found...\n");
		exit(1);
	}

	for (int word_count = 0; word_count < size; word_count++) 
	{
		node *current_node = malloc( sizeof(*current_node) ); //<-- leak here
		node *new_node = malloc( sizeof(*new_node) ); 

		// make sure malloc was successful
		if (current_node == NULL || new_node == NULL)
		{
			printf ("Failed to allocate memory...\n");
			exit(1);
		}

		current_node->next = NULL;
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
			// point to correct bucket
			current_node->next = hash_table[hash_val].next;

			// traverse to the end of the list
			while (current_node->next != NULL)
			{
				current_node = current_node->next;
			}

			//add new node to end of list
			current_node->next = new_node;
		}
	}
	return true;
}

// TODO: return
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

//TODO: 
int get_file_size(FILE *file)
{
	char c;
	int line_count = 0;
	
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

//TODO: 
int hash(char *str)
{
	return (tolower(str[0]) - 97);
}

