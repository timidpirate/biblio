#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].journal, "Phys. Atom. Nucl.") != 0)
		{ printf("Test failed! (expected records[0].journal='Phys. Atom. Nucl.' but was '%s' read)\n", records[0].journal); cleanup(); return; }

	if(strcmp(records[1].journal, "Phys. Rev. D") != 0)
		{ printf("Test failed! (expected records[1].journal='Phys. Rev. D' but was '%s' read)\n", records[1].journal); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
