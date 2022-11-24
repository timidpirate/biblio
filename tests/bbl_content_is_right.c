#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../src/biblio.h"

int main()
{
	if (access(cachefile, F_OK) == 0)	// If cache exists,
		remove(cachefile);				// remove it.
		
	if (access(bblfile, F_OK) == 0)	// If bbl-file exists,
		remove(bblfile);			// remove it.

	load_records();
	sort_db();
	generate_bbl_file();
	cleanup();
	
	FILE * f = fopen(bblfile, "r");
	char buf[1024*5];
	memset(buf,0,1024*5);
	fread(buf, 1, 1024*5, f);
	fclose(f);

	char * exp = "\\begin{thebibliography}{1}\n\n"
				 "\\bibitem{Zykunov:2005tc}\n"
				 "V.A.~Zykunov, Phys. Rev. D {\\bf 75}, 073019, (2007).\n\n"
				 "\\bibitem{Arbuzov:1998yg}\n"
				 "A.B.~Arbuzov, E.A.~Kuraev, F.F.~Tikhonin, B.G.~Shaikhatdenov, Phys. Atom. Nucl. {\\bf 62}, 1393, (1999).\n\n"
				 "\\bibitem{Aaltonen:2008dn}\n"
				 "T.~Aaltonen {\\it{et al.}} (CDF Collaboration), Phys. Rev. D {\\bf 79}, 112002, (2009).\n\n"
				 "\\bibitem{Baier:1973}\n"
				 "V.N.~Baier, V.S.~Fadin, V.M.~Katkov, Emission of relativistic electrons. -- Moscow: Atomizdat, 376 p. (1973).\n\n"
				 "\\bibitem{Bogolyubov:1983gp}\n"
				 "N.N.~Bogolyubov, D.V.~Shirkov, Quantum Fields. -- USA: Benjamin/Cummings, 388 p. (1983).\n\n"
				 "\\bibitem{Voloshin:1984}\n"
				 "М.Б.~Волошин, К.А.~Тер-Мартиросян, Теория калибровочных взаимодействий элементарных частиц. -- Москва: Энергоатомиздат, 296 p. (1984).\n\n"
				 "\\bibitem{Zykunov:NotExisting}\n"
				 "No bib-record for 'Zykunov:NotExisting'.\n\n"
				 "\\end{thebibliography}\n";
	
	if (strcmp(buf, exp) != 0)	// If content of bbl-file is not right...
	{
		printf("Test failed! bbl-file content is wrong:\n");
		printf("expected: '%s'\n", exp);
		printf("actual:   '%s'\n", buf);
		return 1;
	}

	printf("Test passed.\n");
	return 0;
}
