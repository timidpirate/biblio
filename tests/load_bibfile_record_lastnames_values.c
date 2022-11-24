#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].lastnames[0], "Zykunov") != 0)
		{ printf("Test failed! (expected records[0].lastnames[0], 'Zykunov' but was '%s' read)\n", records[0].lastnames[0]); cleanup(); return 1; }

	if(strcmp(records[1].lastnames[0], "Волошин") != 0)
		{ printf("Test failed! (expected records[1].lastnames[0] = 'Волошин' but was '%s' read)\n", records[1].lastnames[0]); cleanup(); return 1; }
	if(strcmp(records[1].lastnames[1], "Тер-Мартиросян") != 0)
		{ printf("Test failed! (expected records[1].lastnames[1] = 'Тер-Мартиросян' but was '%s' read)\n", records[1].lastnames[1]); cleanup(); return 1; }

	if(strcmp(records[2].lastnames[0], "Arbuzov") != 0)
		{ printf("Test failed! (expected records[2].lastnames[0] = 'Arbuzov' but was '%s' read)\n", records[2].lastnames[0]); cleanup(); return 1; }
	if(strcmp(records[2].lastnames[1], "Kuraev") != 0)
		{ printf("Test failed! (expected records[2].lastnames[1] = 'Kuraev' but was '%s' read)\n", records[2].lastnames[1]); cleanup(); return 1; }
	if(strcmp(records[2].lastnames[2], "Tikhonin") != 0)
		{ printf("Test failed! (expected records[2].lastnames[2] = 'Tikhonin' but was '%s' read)\n", records[2].lastnames[2]); cleanup(); return 1; }
	if(strcmp(records[2].lastnames[3], "Shaikhatdenov") != 0)
		{ printf("Test failed! (expected records[2].lastnames[3] = 'Shaikhatdenov' but was '%s' read)\n", records[2].lastnames[3]); cleanup(); return 1; }

	if(strcmp(records[3].lastnames[0], "Aaltonen") != 0)
		{ printf("Test failed! (expected records[4].lastnames[0] = 'Aaltonen' but was '%s' read)\n", records[3].lastnames[0]); cleanup(); return 1; }
	if(strcmp(records[3].lastnames[1], "Adelman") != 0)
		{ printf("Test failed! (expected records[4].lastnames[1] = 'Adelman' but was '%s' read)\n", records[3].lastnames[1]); cleanup(); return 1; }
	if(strcmp(records[3].lastnames[2], "Akimoto") != 0)
		{ printf("Test failed! (expected records[4].lastnames[2] = 'Akimoto' but was '%s' read)\n", records[3].lastnames[2]); cleanup(); return 1; }
	if(strcmp(records[3].lastnames[3], "\\'Alvarez Gonz\\'alez") != 0)
		{ printf("Test failed! (expected records[4].lastnames[3] = '\\'Alvarez Gonz\\'alez' but was '%s' read)\n", records[3].lastnames[3]); cleanup(); return 1; }
	if(strcmp(records[3].lastnames[4], "Amerio") != 0)
		{ printf("Test failed! (expected records[4].lastnames[4] = 'Amerio' but was '%s' read)\n", records[3].lastnames[4]); cleanup(); return 1; }

	if(strcmp(records[6].lastnames[0], "Abbott") != 0)
		{ printf("Test failed! (expected records[6].lastnames[0] = 'Abbott' but was '%s' read)\n", records[6].lastnames[0]); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
