#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].pages, "1529") != 0)
		{ printf("Test failed! (expected records[0].pages='1529' but was '%s' read)\n", records[0].pages); cleanup(); return; }

	if(strcmp(records[1].pages, "3453") != 0)
		{ printf("Test failed! (expected records[1].pages='3453' but was '%s' read)\n", records[1].pages); cleanup(); return; }

	if(strcmp(records[3].pages, "112002") != 0)
		{ printf("Test failed! (expected records[3].pages='112002' but was '%s' read)\n", records[3].pages); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
