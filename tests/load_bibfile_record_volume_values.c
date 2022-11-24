#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].volume, "67") != 0)
		{ printf("Test failed! (expected records[0].volume='67' but was '%s' read)\n", records[0].volume); cleanup(); return; }

	if(strcmp(records[1].volume, "16") != 0)
		{ printf("Test failed! (expected records[1].volume='16' but was '%s' read)\n", records[1].volume); cleanup(); return; }

	if(strcmp(records[2].volume, "62") != 0)
		{ printf("Test failed! (expected records[2].volume='62' but was '%s' read)\n", records[2].volume); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
