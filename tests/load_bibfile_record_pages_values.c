#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].pages, "073019") != 0)
		{ printf("Test failed! (expected records[0].pages='073019' but was '%s' read)\n", records[0].pages); cleanup(); return 1; }

	if(strcmp(records[1].pages, "296") != 0)
		{ printf("Test failed! (expected records[1].pages='296' but was '%s' read)\n", records[1].pages); cleanup(); return 1; }

	if(strcmp(records[2].pages, "1393") != 0)
		{ printf("Test failed! (expected records[2].pages='1393' but was '%s' read)\n", records[2].pages); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
