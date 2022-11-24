#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].title, "Weak radiative corrections to Drell-Yan process for large invariant mass of di-lepton pair") != 0)
		{ printf("Test failed! (expected records[0].title='Weak radiative corrections to Drell-Yan process for large invariant mass of di-lepton pair' but was '%s' read)\n", records[0].title); cleanup(); return 1; }

	if(strcmp(records[1].title, "Теория калибровочных взаимодействий элементарных частиц") != 0)
		{ printf("Test failed! (expected records[1].title='Теория калибровочных взаимодействий элементарных частиц' but was '%s' read)\n", records[1].title); cleanup(); return 1; }

	if(strcmp(records[2].title, "Radiative corrections to the process $\\mu^+ \\mu^- \\to H \\gamma$") != 0)
		{ printf("Test failed! (expected records[2].title='Radiative corrections to the process $\\mu^+ \\mu^- \\to H \\gamma$' but was '%s' read)\n", records[2].title); cleanup(); return 1; }

	printf("Test passed.\n");
	cleanup();
	return 0;
}
