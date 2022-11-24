#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[4].publisher, "Atomizdat") != 0)
		{ printf("Test failed! (expected records[4].publisher='Atomizdat' but was '%s' read)\n", records[4].publisher); cleanup(); return 1; }

	if(strcmp(records[1].publisher, "Энергоатомиздат") != 0)
		{ printf("Test failed! (expected records[1].publisher='Энергоатомиздат' but was '%s' read)\n", records[1].publisher); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
