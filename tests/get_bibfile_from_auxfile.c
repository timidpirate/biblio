#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	extract_bibfile();
	
	if(strcmp(bibfile, "/mnt/d/Projects/Biblio/tests/biblio.bib") != 0)
		{ printf("Test failed! (expected bibfile='/mnt/d/Projects/Biblio/tests/biblio.bib' but was '%s' key read)\n", bibfile); return; }

	printf("Test passed.\n");
}
