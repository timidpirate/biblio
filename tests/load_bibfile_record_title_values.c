#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	int num = count_bib_records();
	records = (record *) malloc(num * sizeof(record));
	
	load_bibfile();
	
	if(strcmp(records[0].title, "Radiative decays of $\\phi$-meson about nature of light scalar resonances") != 0)
		{ printf("Test failed! (expected records[0].title='Radiative decays of $\\phi$-meson about nature of light scalar resonances' but was '%s' read)\n", records[0].title); cleanup(); return; }

	if(strcmp(records[1].title, "Is an electron's Charge Independent of Its Velocity?") != 0)
		{ printf("Test failed! (expected records[1].title='Is an electron's Charge Independent of Its Velocity?' but was '%s' read)\n", records[1].title); cleanup(); return; }

	if(strcmp(records[2].title, "Radiative corrections to the process $\\mu^+ \\mu^- \\to H \\gamma$") != 0)
		{ printf("Test failed! (expected records[2].title='Radiative corrections to the process $\\mu^+ \\mu^- \\to H \\gamma$' but was '%s' read)\n", records[2].title); cleanup(); return; }

	printf("Test passed.\n");
	cleanup();
}
