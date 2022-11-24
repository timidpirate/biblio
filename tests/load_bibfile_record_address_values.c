#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[1].address, "Москва") != 0)
		{ printf("Test failed! (expected records[1].address='Москва' but was '%s' read)\n", records[1].address); cleanup(); return 1; }

	if(strcmp(records[5].address, "USA") != 0)
		{ printf("Test failed! (expected records[5].address='USA' but was '%s' read)\n", records[5].address); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
