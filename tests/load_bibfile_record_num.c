#include <stdio.h>
#include <malloc.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	load_bibfile();
	
	if(record_num == 1143)
		printf("Test passed.\n");
	else
		printf("Test failed! (expected 1143 but was %d records read)\n", record_num);
		
	cleanup();
}
