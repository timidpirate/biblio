#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(records[0].type != 1)
		{ printf("Test failed! (expected records[0].type=1 but was '%d' read)\n", records[0].type); cleanup(); return; }

	if(records[1].type != 1)
		{ printf("Test failed! (expected records[1].type=1 but was '%d' read)\n", records[1].type); cleanup(); return; }

	if(records[5].type != 2)
		{ printf("Test failed! (expected records[5].type=2 but was '%d' read)\n", records[5].type); cleanup(); return; }

	if(records[6].type != 2)
		{ printf("Test failed! (expected records[6].type=2 but was '%d' read)\n", records[6].type); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
