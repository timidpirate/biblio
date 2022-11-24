#include <stdio.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	
	if(num != 7)
		{ printf("Test failed! (expected 7 but was %d records read)\n", num); cleanup(); return 1; }
		
	printf("Test passed.\n");
	cleanup();
	return 0;
}
