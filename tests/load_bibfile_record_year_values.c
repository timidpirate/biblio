#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].year, "2007") != 0)
		{ printf("Test failed! (expected records[0].year='2007' but was '%s' read)\n", records[0].year); cleanup(); return 1; }

	if(strcmp(records[1].year, "1984") != 0)
		{ printf("Test failed! (expected records[1].year='1984' but was '%s' read)\n", records[1].year); cleanup(); return 1; }

	if(strcmp(records[2].year, "1999") != 0)
		{ printf("Test failed! (expected records[2].year='1999' but was '%s' read)\n", records[2].year); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
