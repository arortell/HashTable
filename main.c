#include <stdio.h>
#include <stdlib.h>

#include "hashTable.h"

int main(int argc, char **argv) 
{
	char *file_name = "large";
	
	char *word = "shit";
	
	
	key_hash_t(file_name);
	
	
	load_hash_t(file_name);
	
	bool result = check(word);

	if(result)
	{
		printf("YES");
	}

	int uisize = size();
	unload_hash_t();
	
	
	printf("Number of nodes = (%ui)\n", uisize);
	//printf("Number of chars in %s = (%lu)\n", word, strlen(word));
	
    return 0;
}
