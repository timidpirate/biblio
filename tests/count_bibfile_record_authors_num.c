#include <stdio.h>
#include <malloc.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	// Single author.
	if(records[0].authors_num != 1)
		{ printf("Test failed! (expected records[0].authors_num=1 but was '%d' read)\n", records[0].authors_num); cleanup(); return; }

	// Two authors.
	if(records[1].authors_num != 2)
		{ printf("Test failed! (expected records[1].authors_num=2 but was '%d' read)\n", records[1].authors_num); cleanup(); return; }

	// Four authors.
	if(records[2].authors_num != 4)
		{ printf("Test failed! (expected records[2].authors_num=4 but was '%d' read)\n", records[2].authors_num); cleanup(); return; }

	// More then 5 authors.
	if(records[3].authors_num != 5)
		{ printf("Test failed! (expected records[3].authors_num=5 but was '%d' read)\n", records[3].authors_num); cleanup(); return; }

	// Author and others.
	if(records[4].authors_num != 1)
		{ printf("Test failed! (expected records[4].authors_num=1 but was '%d' read)\n", records[4].authors_num); cleanup(); return; }

	printf("Test passed.\n");
	
	cleanup();
}
