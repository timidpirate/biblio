#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/biblio.h"

void main()
{
	if (access(cachefile, F_OK) == 0)	// If cache exists,
		remove(cachefile);				// remove it.

	char buf[256], * exp;
	record key, * r;

//	printf("\nload_records...\n");
	load_records();
//	printf("sort_db...\n");
	sort_db();
	
	// Single author.
	strcpy(key.bibkey, "Zykunov:2005tc");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
//	printf("pre format_article...\n");
	format_article(buf, r);
//	printf("post format_article...\n");

	exp = "\\bibitem{Zykunov:2005tc}\n"
		  "V.A.~Zykunov, Phys. Rev. D {\\bf 75}, 073019, (2007).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return;
	}

	// Few authors.
	strcpy(key.bibkey, "Arbuzov:1998yg");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_article(buf, r);

	exp = "\\bibitem{Arbuzov:1998yg}\n"
		  "A.B.~Arbuzov, E.A.~Kuraev, F.F.~Tikhonin, B.G.~Shaikhatdenov, Phys. Atom. Nucl. {\\bf 62}, 1393, (1999).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return;
	}

	// More then five authors and collaboration.
	strcpy(key.bibkey, "Aaltonen:2008dn");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_article(buf, r);

	exp = "\\bibitem{Aaltonen:2008dn}\n"
		  "T.~Aaltonen {\\it{et al.}} (CDF Collaboration), Phys. Rev. D {\\bf 79}, 112002, (2009).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return;
	}

	// Author and others give et al.
	strcpy(key.bibkey, "Abbiendi:2004xa");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_article(buf, r);

	exp = "\\bibitem{Abbiendi:2004xa}\n"
		  "G.~Abbiendi {\\it{et al.}} (OPAL Collaboration), Eur. Phys. J. C {\\bf 35}, 437, (2004).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return;
	}

	printf("Test passed.\n");
	cleanup();
}
