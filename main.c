#include <stdio.h>
#include <stdlib.h>

#include "hashTable.h"


int main(int argc, char **argv) 
{
	char *file_name = "large";
	
	key_hash_t(file_name);
	
	
	load_hash_t(file_name);
	
	int uisize = size();
	unload_hash_t();
	printf("%ui\n", uisize);
	
    return 0;
}
