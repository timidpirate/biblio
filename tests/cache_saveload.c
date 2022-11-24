#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	record r;
	
	record_num = 2;
	
	records = (record *) malloc(record_num * sizeof(record));

	strcpy(r.bibkey, "Key1");
	r.type = 1;
	r.authors_num = 1;
	strcpy(r.initials[0], "M.A.");
	strcpy(r.lastnames[0], "Ivanov");
	strcpy(r.title, "Study of some new ideas");
	strcpy(r.journal, "Phys. Rev. D");
	strcpy(r.year, "1995");
	strcpy(r.volume, "13");
	strcpy(r.pages, "10-20");
	records[0] = r;
	
	strcpy(r.bibkey, "Key2");
	r.type = 2;
	r.authors_num = 2;
	strcpy(r.initials[0], "Л.Д.");
	strcpy(r.initials[1], "Е.М.");
	strcpy(r.lastnames[0], "Ландау");
	strcpy(r.lastnames[1], "Лифшиц");
	strcpy(r.title, "Механика");
	strcpy(r.publisher, "ГИТТЛ");
	strcpy(r.address, "Москва");
	strcpy(r.year, "1940");
	strcpy(r.pages, "200");
	records[1] = r;

	save_cache();
	
	free(records);
	
	record_num = load_cache();
	if(record_num == 0)
		{ printf("Test failed! (load_cache returned zero number of records)\n"); free(records); return;}
	
	if(strcmp(records[0].bibkey,"Key1") != 0)
		{ printf("Test failed! (expected records[0].bibkey = 'Key1' but was '%s' read)\n", records[0].bibkey); free(records); return;}
	if(strcmp(records[1].bibkey,"Key2") != 0)
		{ printf("Test failed! (expected records[1].bibkey = 'Key2' but was '%s' read)\n", records[1].bibkey); free(records); return;}
		
	if(strcmp(records[0].initials[0],"M.A.") != 0)
		{ printf("Test failed! (expected records[0].initials[0] = 'M.A.' but was '%s' read)\n", records[0].initials[0]); free(records); return;}
	if(strcmp(records[1].initials[0],"Л.Д.") != 0)
		{ printf("Test failed! (expected records[1].initials[0] = 'Л.Д.' but was '%s' read)\n", records[1].initials[0]); free(records); return;}

	if(strcmp(records[1].initials[1],"Е.М.") != 0)
		{ printf("Test failed! (expected records[1].initials[1] = 'Е.М.' but was '%s' read)\n", records[1].initials[1]); free(records); return;}

	if(strcmp(records[0].lastnames[0],"Ivanov") != 0)
		{ printf("Test failed! (expected records[0].lastnames[0] = 'Ivanov' but was '%s' read)\n", records[0].lastnames[0]); free(records); return;}
	if(strcmp(records[1].lastnames[0],"Ландау") != 0)
		{ printf("Test failed! (expected records[1].lastnames[0] = 'Ландау' but was '%s' read)\n", records[1].lastnames[0]); free(records); return;}

	if(strcmp(records[1].lastnames[1],"Лифшиц") != 0)
		{ printf("Test failed! (expected records[1].lastnames[1] = 'Лифшиц' but was '%s' read)\n", records[1].lastnames[1]); free(records); return;}

	if(strcmp(records[0].title,"Study of some new ideas") != 0)
		{ printf("Test failed! (expected records[0].title = 'Study of some new ideas' but was '%s' read)\n", records[0].title); free(records); return;}
	if(strcmp(records[1].title,"Механика") != 0)
		{ printf("Test failed! (expected records[1].title = 'Механика' but was '%s' read)\n", records[1].title); free(records); return;}

	if(strcmp(records[0].journal,"Phys. Rev. D") != 0)
		{ printf("Test failed! (expected records[0].journal = 'Phys. Rev. D' but was '%s' read)\n", records[0].journal); free(records); return;}
		
	if(strcmp(records[1].publisher,"ГИТТЛ") != 0)
		{ printf("Test failed! (expected records[1].publisher = 'ГИТТЛ' but was '%s' read)\n", records[1].publisher); free(records); return;}

	if(strcmp(records[0].volume,"13") != 0)
		{ printf("Test failed! (expected records[0].volume = '13' but was '%s' read)\n", records[0].volume); free(records); return;}
		
	if(strcmp(records[1].address,"Москва") != 0)
		{ printf("Test failed! (expected records[1].address = 'Москва' but was '%s' read)\n", records[1].address); free(records); return;}

	if(strcmp(records[0].year,"1995") != 0)
		{ printf("Test failed! (expected records[0].year = '1995' but was '%s' read)\n", records[0].year); free(records); return;}
	if(strcmp(records[1].year,"1940") != 0)
		{ printf("Test failed! (expected records[1].year = '1940' but was '%s' read)\n", records[1].year); free(records); return;}

	if(strcmp(records[0].pages,"10-20") != 0)
		{ printf("Test failed! (expected records[0].pages = '10-20' but was '%s' read)\n", records[0].pages); free(records); return;}
	if(strcmp(records[1].pages,"200") != 0)
		{ printf("Test failed! (expected records[1].pages = '200' but was '%s' read)\n", records[1].pages); free(records); return;}

	printf("Test passed.\n");
	free(records);
}
