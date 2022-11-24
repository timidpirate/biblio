#include "biblio.h"

int main( int argc, char ** argv )
{
	if(argc == 1)
	{
		printf("Error! No arguments.\n\nUsage:\n\tbiblio <aux-file>\n");
		return -1;
	}

	sprintf(auxfile, "%s.aux", argv[1]);
	printf("auxfile = '%s'\n",auxfile);
	
	extract_bibfile();
	printf("bibfile = '%s'\n",bibfile);
	
	sprintf(cachefile, "%s.cache", bibfile);
	printf("cachefile = '%s'\n",cachefile);
	
	sprintf(bblfile, "%s.bbl", argv[1]);
	printf("bblfile = '%s'\n",bblfile);

	printf("load_records...\n");
	load_records();
	printf("sort_db...\n");
	sort_db();
	printf("generate_bbl_file...\n");
	generate_bbl_file();
	printf("cleanup...\n");
	cleanup();
	
	return 0;
}
