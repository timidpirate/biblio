#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../src/biblio.h"

int main()
{
	struct stat c;	// Cache file stats for time changing.
	
	if (access(cachefile, F_OK) != 0)	// If cache is not exist,
		save_cache();					// create it.

	// Set modification time of bib-file to be older then the cache file.
	struct utimbuf b;
	stat(cachefile, &c);				// Get cache modification time.
	b.actime =  c.st_atim.tv_sec - 5; /* set last access  time to 'cache access time - 5sec' */
	b.modtime = c.st_mtim.tv_sec - 5; /* set modification time to 'cache modification time - 5sec' */
	utime(bibfile, &b);
	
	load_records();
	
	// Cache must be renewed.
    struct stat c2;
    stat(cachefile, &c2);	// Get cache modification time.
    
	if (c2.st_mtim.tv_sec != c.st_mtim.tv_sec)	// If time of modification of cache file changed, then cache was regenerated.
	{
		printf("Test failed! (cache file was regenerated while bib file is older)\n");
		printf("             (bibfile.modtime = %ld)\n", b.modtime);
		printf("             (cache.st_mtime  = %lld.%.9ld)\n", (long long)c.st_mtim.tv_sec, c.st_mtim.tv_nsec);
		printf("             (cache2.st_mtime = %lld.%.9ld)\n", (long long)c2.st_mtim.tv_sec, c2.st_mtim.tv_nsec);
		return 1;
	}

	printf("Test passed.\n");
	return 0;
}
