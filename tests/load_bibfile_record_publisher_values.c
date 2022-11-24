#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[5].publisher, "Atomizdat") != 0)
		{ printf("Test failed! (expected records[5].publisher='Atomizdat' but was '%s' read)\n", records[5].publisher); cleanup(); return; }

	if(strcmp(records[6].publisher, "Энергоатомиздат") != 0)
		{ printf("Test failed! (expected records[6].publisher='Энергоатомиздат' but was '%s' read)\n", records[6].publisher); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
