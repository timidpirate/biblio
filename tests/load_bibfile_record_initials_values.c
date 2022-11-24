#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].initials[0], "V.A.") != 0)
		{ printf("Test failed! (expected records[0].initials[0], 'V.A.' but was '%s' read)\n", records[0].initials[0]); cleanup(); return 1; }

	if(strcmp(records[1].initials[0], "М.Б.") != 0)
		{ printf("Test failed! (expected records[1].initials[0], 'М.Б.' but was '%s' read)\n", records[1].initials[0]); cleanup(); return 1; }
	if(strcmp(records[1].initials[1], "К.А.") != 0)
		{ printf("Test failed! (expected records[1].initials[1], 'К.А.' but was '%s' read)\n", records[1].initials[1]); cleanup(); return 1; }

	if(strcmp(records[2].initials[0], "A.B.") != 0)
		{ printf("Test failed! (expected records[2].initials[0], 'A.B.' but was '%s' read)\n", records[2].initials[0]); cleanup(); return 1; }
	if(strcmp(records[2].initials[1], "E.A.") != 0)
		{ printf("Test failed! (expected records[2].initials[1], 'E.A.' but was '%s' read)\n", records[2].initials[1]); cleanup(); return 1; }
	if(strcmp(records[2].initials[2], "F.F.") != 0)
		{ printf("Test failed! (expected records[2].initials[1], 'F.F.' but was '%s' read)\n", records[2].initials[2]); cleanup(); return 1; }
	if(strcmp(records[2].initials[3], "B.G.") != 0)
		{ printf("Test failed! (expected records[2].initials[1], 'B.G.' but was '%s' read)\n", records[2].initials[3]); cleanup(); return 1; }

	if(strcmp(records[4].initials[0], "V.N.") != 0)
		{ printf("Test failed! (expected records[4].initials[0] = 'V.N.' but was '%s' read)\n", records[4].initials[0]); cleanup(); return 1; }
	if(strcmp(records[4].initials[1], "V.S.") != 0)
		{ printf("Test failed! (expected records[4].initials[1] = 'V.S.' but was '%s' read)\n", records[4].initials[1]); cleanup(); return 1; }
	if(strcmp(records[4].initials[2], "V.M.") != 0)
		{ printf("Test failed! (expected records[4].initials[2] = 'V.M.' but was '%s' read)\n", records[4].initials[2]); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
