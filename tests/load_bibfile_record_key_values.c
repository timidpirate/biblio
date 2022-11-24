#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].bibkey, "Achasov:2003cn") != 0)
		{ printf("Test failed! (expected records[0].bibkey='Achasov:2003cn' but was '%s' key read)\n", records[0].bibkey); cleanup(); return; }

	if(strcmp(records[1].bibkey, "Bartlett:1977gu") != 0)
		{ printf("Test failed! (expected records[1].bibkey='Bartlett:1977gu' but was '%s' key read)\n", records[1].bibkey); cleanup(); return; }

	if(strcmp(records[2].bibkey, "Arbuzov:1998yg") != 0)
		{ printf("Test failed! (expected records[2].bibkey='Arbuzov:1998yg' but was '%s' key read)\n", records[2].bibkey); cleanup(); return; }

	if(strcmp(records[3].bibkey, "Aaltonen:2008dn") != 0)
		{ printf("Test failed! (expected records[3].bibkey='Aaltonen:2008dn' but was '%s' key read)\n", records[3].bibkey); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
