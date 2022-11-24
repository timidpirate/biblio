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
	
	strcpy(key.bibkey, "Baier:1973");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_book(buf, r);

	exp = "\\bibitem{Baier:1973}\n"
		  "V.N.~Baier, V.S.~Fadin, V.M.~Katkov, Emission of relativistic electrons. -- Moscow: Atomizdat, 376 p. (1973).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return 1;
	}

	strcpy(key.bibkey, "Bogolyubov:1983gp");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_book(buf, r);

	exp = "\\bibitem{Bogolyubov:1983gp}\n"
		  "N.N.~Bogolyubov, D.V.~Shirkov, Quantum Fields. -- USA: Benjamin/Cummings, 388 p. (1983).\n";
	
	if (strcmp(buf, exp) != 0)
	{
		printf("Test failed!\n");
		printf("\texpected: '%s'\n", exp);
		printf("\tactual:   '%s'\n", buf);
		return 1;
	}

	strcpy(key.bibkey, "Voloshin:1984");
	r = (record *)bsearch(&key, records, record_num, sizeof(record), compare_records);
	format_book(buf, r);

	exp = "\\bibitem{Voloshin:1984}\n"
		  "М.Б.~Волошин, К.А.~Тер-Мартиросян, Теория калибровочных взаимодействий элементарных частиц. -- Москва: Энергоатомиздат, 296 p. (1984).\n";
	
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
