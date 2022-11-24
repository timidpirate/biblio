#include <stdio.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	strcpy(bibfile, "./empty_biblio.bib");
	
	int num = count_bib_records();
	
	if(num != 0)
		{ printf("Test failed! (expected 0 but was %d records read)\n", num); return 1; }
		
	printf("Test passed.\n");
	return 0;
}
