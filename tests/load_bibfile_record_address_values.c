#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[5].address, "Moscow") != 0)
		{ printf("Test failed! (expected records[5].address='Moscow' but was '%s' read)\n", records[5].address); cleanup(); return; }

	if(strcmp(records[6].address, "Москва") != 0)
		{ printf("Test failed! (expected records[6].address='Москва' but was '%s' read)\n", records[6].address); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
