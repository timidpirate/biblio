#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/biblio.h"

int main()
{
	if (access(cachefile, F_OK) == 0)	// If cache exists,
		remove(cachefile);				// remove it.

	char buf[256], * exp;
	record key, * r;

	load_records();
	sort_db();
	
	// Single author.
	strcpy(key.bibkey, "Zykunov:2005tc");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_article(buf, r);

	exp = "\\bibitem{Zykunov:2005tc}\n"
		  "V.A.~Zykunov, Phys. Rev. D {\\bf 75}, 073019, (2007).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return 1;
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
		return 1;
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
		return 1;
	}

	// Author and others give et al.
	strcpy(key.bibkey, "Abbott:1999se");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_article(buf, r);

	exp = "\\bibitem{Abbott:1999se}\n"
		  "B.~Abbott {\\it{et al.}} (D0 Collaboration), Phys. Lett. B {\\bf 487}, 264, (2000).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return 1;
	}

	printf("Test passed.\n");
	cleanup();
	return 0;
}
