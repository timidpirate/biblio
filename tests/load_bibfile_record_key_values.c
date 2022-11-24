#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].bibkey, "Zykunov:2005tc") != 0)
		{ printf("Test failed! (expected records[0].bibkey='Zykunov:2005tc' but was '%s' key read)\n", records[0].bibkey); cleanup(); return 1; }

	if(strcmp(records[1].bibkey, "Voloshin:1984") != 0)
		{ printf("Test failed! (expected records[1].bibkey='Voloshin:1984' but was '%s' key read)\n", records[1].bibkey); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
