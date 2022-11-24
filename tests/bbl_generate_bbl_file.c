#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../src/biblio.h"

int main()
{
	if (access(bblfile, F_OK) == 0)	// If bbl-file exists,
		remove(bblfile);			// remove it.
		
	generate_bbl_file();

	if (access(bblfile, F_OK) != 0)	// If bbl-file is not generated...
	{
		printf("Test failed! (bbl-file was not generated)\n");
		return 1;
	}

	printf("Test passed.\n");
	return 0;
}
