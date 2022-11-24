#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(records[0].type != 1)
		{ printf("Test failed! (expected records[0].type=1 but was '%d' read)\n", records[0].type); cleanup(); return 1; }

	if(records[1].type != 2)
		{ printf("Test failed! (expected records[1].type=2 but was '%d' read)\n", records[1].type); cleanup(); return 1; }

	if(records[2].type != 1)
		{ printf("Test failed! (expected records[2].type=1 but was '%d' read)\n", records[2].type); cleanup(); return 1; }

	if(records[4].type != 2)
		{ printf("Test failed! (expected records[4].type=2 but was '%d' read)\n", records[4].type); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
