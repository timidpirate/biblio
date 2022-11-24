#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].volume, "75") != 0)
		{ printf("Test failed! (expected records[0].volume='75' but was '%s' read)\n", records[0].volume); cleanup(); return 1; }

	if(strcmp(records[2].volume, "62") != 0)
		{ printf("Test failed! (expected records[2].volume='62' but was '%s' read)\n", records[2].volume); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
