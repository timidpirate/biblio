#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].year, "2004") != 0)
		{ printf("Test failed! (expected records[0].year='2004' but was '%s' read)\n", records[0].year); cleanup(); return; }

	if(strcmp(records[1].year, "1977") != 0)
		{ printf("Test failed! (expected records[1].year='1977' but was '%s' read)\n", records[1].year); cleanup(); return; }

	if(strcmp(records[2].year, "1999") != 0)
		{ printf("Test failed! (expected records[2].year='1999' but was '%s' read)\n", records[2].year); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
