#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include "../src/biblio.h"

int main()
{
	struct stat c;	// Cache file stats for time changing.

	if (access(cachefile, F_OK) != 0)	// If cache is not exist,
		save_cache();					// create it.

	// Set modification time of bib-file to be later then the cache file.
	struct utimbuf b;
	stat(cachefile, &c);				// Get cache modification time.
	b.actime =  c.st_atim.tv_sec + 1;	// set last access  time to 'cache access time + 1 sec'
	b.modtime = c.st_mtim.tv_sec + 1;	// set modification time to 'cache modification time + 1 sec'
	utime(bibfile, &b);
	
	sleep(1);
	
	// Cache must be renewed.
	load_records();
	cleanup();
	
    stat(cachefile, &c);	// Get cache modification time.
    
	if (b.modtime > c.st_mtim.tv_sec)	// If time of modification of bib-file is later then of cache, then cache was not renewed.
	{
		printf("Test failed! (cache file is older then bib file)\n");
		printf("             (bibfile.modtime = %ld)\n", b.modtime);
		printf("             (cache.st_mtime  = %lld.%.9ld)\n", (long long)c.st_mtim.tv_sec,    c.st_mtim.tv_nsec);
		return 1;
	}

	printf("Test passed.\n");
	return 0;
}
