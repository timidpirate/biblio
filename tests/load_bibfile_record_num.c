#include <stdio.h>
#include <malloc.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	load_bibfile();
	
	if(record_num == 7)
		printf("Test passed.\n");
	else
		printf("Test failed! (expected 7 but was %d records read)\n", record_num);
		
	cleanup();
	return 0;
}
