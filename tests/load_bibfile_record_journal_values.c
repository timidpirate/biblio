#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].journal, "Phys. Rev. D") != 0)
		{ printf("Test failed! (expected records[0].journal='Phys. Rev. D' but was '%s' read)\n", records[0].journal); cleanup(); return 1; }

	if(strcmp(records[2].journal, "Phys. Atom. Nucl.") != 0)
		{ printf("Test failed! (expected records[2].journal='Phys. Atom. Nucl.' but was '%s' read)\n", records[2].journal); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
