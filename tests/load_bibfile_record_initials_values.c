#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].initials[0], "N. N.") != 0)
		{ printf("Test failed! (expected records[0].initials[0], 'N. N.' but was '%s' read)\n", records[0].initials[0]); cleanup(); return; }

	if(strcmp(records[1].initials[0], "D. F.") != 0)
		{ printf("Test failed! (expected records[1].initials[0] = 'D. F.' but was '%s' read)\n", records[1].initials[0]); cleanup(); return; }
	if(strcmp(records[1].initials[1], "B. F. L.") != 0)
		{ printf("Test failed! (expected records[1].initials[1] = 'B. F. L.' but was '%s' read)\n", records[1].initials[1]); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
