#include <stdio.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	
	if(num == 1143)
		printf("Test passed.\n");
	else
		printf("Test failed! (expected 1143 but was %d records read)\n", num);
		
	cleanup();
}
