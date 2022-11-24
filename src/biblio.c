#include <stdlib.h>
#include "biblio.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int record_num;

record * records;

char auxfile[256]   = "./text.aux";

char bibfile[256]   = "./biblio.bib";
char cachefile[512] = "./biblio.bib.cache";

//char bibfile[256]   = "/mnt/d/Physics/Bibliography/Main8.bib";
//char cachefile[512] = "/mnt/d/Physics/Bibliography/Main8.bib.cache";

char bblfile[256]   = "./text.bbl";

void cleanup(void)
{
	if(records != NULL) free(records);
}

int compare_records(const void * r1, const void * r2)
{
	return strcmp(((record*)r1)->bibkey, ((record*)r2)->bibkey);
}

void extract_bibfile(void)
{
	FILE * f = NULL;
	char str[256];

	f = fopen(auxfile, "r");

	if(f == NULL)
	{
		printf("Cannot open file \"%s\".\n", auxfile);
		return;
	}	

	while(fgets(str,256,f) != NULL)
		if(strncmp(str,"\\bibdata",8) == 0)
		{
			sprintf(bibfile, "%s.bib", get_bibdata(str));
//			printf("bibfile: %s\n", bibfile);
			break;
		}
		
	fclose(f);
}

char * get_bibdata(char str[256])
{
	int len = strlen(str);	// Cut final bracket.
	str[len-2] = 0;

	return strstr(str, ",") + 1;
}

void load_records(void)
{
	if (access(cachefile, F_OK) == 0)	// If cache exists,
	{
		struct stat b, c;
		stat(bibfile,   &b);
		stat(cachefile, &c);
		
		if(b.st_mtim.tv_sec < c.st_mtim.tv_sec)	// Bibfile is older then cache...
			record_num = load_cache();			// then use the cache.
		else
		{										// If not...
			record_num = load_bibfile();		// use bib-file
			save_cache();						// and regenerate cache.
		}
	}
	else   									// If cache does not exist then
	{
		record_num = load_bibfile();        // load bib-file...
		save_cache();						// and generate cache.
	}
	
	for(int i = 0 ; i < record_num ; i++)
		records[i].already_used = 0;
}

int count_bib_records(void)
{
	FILE * f = NULL;
	char str[256];
	int num = 0;
	
	f = fopen(bibfile, "r");
	
	if(f == NULL)
	{
		printf("Cannot open file \"%s\".\n", bibfile);
		return 0;
	}	
	
	while(fgets(str,256,f) != NULL)
	{
		trim(str);
		
		if(strlen(str) == 0) continue;
		
		if(str[0] == '@')
		{
			if((strncmp(str,"@Book",5) == 0) || (strncmp(str,"@book",5) == 0))
			{
				num++;
				continue;
			}
			
			if((strncmp(str,"@Article",8) == 0) || (strncmp(str,"@article",8) == 0))
			{
				num++;
				continue;
			}
		}
	}
	
	fclose(f);
	
	return num;
}

int load_bibfile(void)
{
//	printf("\nload_bibfile %s...\n", bibfile);

	record_num = count_bib_records();
	if(record_num == 0) return 0;
	
//	printf("malloc %d elements...\n", record_num);
	records = (record *) malloc(record_num * sizeof(record));

	FILE * f = NULL;
	char str[256];
	int record_index = 0;

//	printf("open bib file...\n");
	f = fopen(bibfile, "r");

	if(f == NULL)
	{
		printf("Cannot open file \"%s\".\n", bibfile);
		return 0;
	}	

	while(fgets(str,256,f) != NULL)
	{
		trim(str);
		if(strlen(str) == 0) continue;

		if(str[0] == '@')
		{
			if((strncmp(str,"@Article",8) == 0) || (strncmp(str,"@article",8) == 0))
			{
//				printf("before load article... record_index = %d\n", record_index);
				records[record_index] = load_article(f,str);
//				printf("after load article...\n");
				record_index++;
				continue;
			}

			if((strncmp(str,"@Book",5) == 0) || (strncmp(str,"@book",5) == 0))
			{
//				printf("loading book...\n");
				records[record_index] = load_book(f,str);
				record_index++;
				continue;
			}
		}
	}
	fclose(f);
	
	return record_num;
}

void sort_db(void)
{
	qsort(records,record_num, sizeof(record), &compare_records);
}

record load_article(FILE * f, char str[256])
{
	record r;
	memset(&r, 0, sizeof(record));
	
	r.type = 1;

	strcpy(r.bibkey, get_bibkey(str));
	
//	printf("loading article %s...\n", r.bibkey);
	
	while(str[0] != '}')
	{
		if(fgets(str,256,f) == NULL) break;

//		printf("pre-trim...\n");
		trim(str);
//		printf("post-trim...\n");
		if(strlen(str) == 0) continue;
		
		//author
		if((strncmp(str,"author",6) == 0) || (strncmp(str,"Author",6) == 0))
		{
//			printf("authors...\n");
			r.authors_num = get_five_authors(str,&r);
//			printf("author (%d)...\n", r.authors_num);
			continue;
		}

		//title
		if((strncmp(str,"title",5) == 0) || (strncmp(str,"Title",5) == 0))
		{
//			printf("titles...\n");
			strcpy(r.title, get_title(str));
//			printf("title (%s)...\n", r.title);
			continue;
		}

		//journal
		if((strncmp(str,"journal",7) == 0) || (strncmp(str,"Journal",7) == 0))
		{
//			printf("journals...\n");
			strcpy(r.journal, get_value(str));
//			printf("journal (%s)...\n", r.journal);
			continue;
		}

		//year
		if((strncmp(str,"year",4) == 0) || (strncmp(str,"Year",4) == 0))
		{
//			printf("years...str = %s\n", str);
			strcpy(r.year, get_value(str));
//			printf("year (%s)...\n", r.year);
			continue;
		}

		//volume
		if((strncmp(str,"volume",6) == 0) || (strncmp(str,"Volume",6) == 0))
		{
//			printf("volumes...\n");
			strcpy(r.volume, get_value(str));
//			printf("volume (%s)...\n", r.volume);
			continue;
		}

		//pages
		if((strncmp(str,"pages",5) == 0) || (strncmp(str,"Pages",5) == 0))
		{
//			printf("pages...\n");
			char * pages = get_value(str);
			char * delim = strstr(pages, "-");
			if(delim == NULL)
				strcpy(r.pages, pages);
			else
				strncpy(r.pages, pages, delim - pages);
			
//			printf("pages (%s)...\n", r.pages);
			continue;
		}

		//collaboration
		if((strncmp(str,"collaboration",13) == 0) || (strncmp(str,"Collaboration",13) == 0))
		{
//			printf("collaborations...\n");
			strcpy(r.collaboration, get_value(str));
//			printf("collaboration (%s)...\n", r.collaboration);
			continue;
		}
	}
	
//	printf("exit load_article...\n");
	return r;
}

record load_book(FILE * f, char str[256])
{
	record r;
	memset(&r, 0, sizeof(record));

	r.type = 2;

	strcpy(r.bibkey, get_bibkey(str));
				
	while(str[0] != '}')
	{
		if(fgets(str,256,f) == NULL) break;
		
		trim(str);
		if(strlen(str) == 0) continue;

		//author
		if((strncmp(str,"author",6) == 0) || (strncmp(str,"Author",6) == 0))
		{
			r.authors_num = get_five_authors(str,&r);
			continue;
		}

		//title
		if((strncmp(str,"title",5) == 0) || (strncmp(str,"Title",5) == 0))
		{
			strcpy(r.title, get_title(str));
			continue;
		}

		//year
		if((strncmp(str,"year",4) == 0) || (strncmp(str,"Year",4) == 0))
		{
			strcpy(r.year, get_value(str));
			continue;
		}

		//pages
		if((strncmp(str,"pages",5) == 0) || (strncmp(str,"Pages",5) == 0))
		{
			strcpy(r.pages, get_value(str));
			continue;
		}

		//publisher
		if((strncmp(str,"publisher",9) == 0) || (strncmp(str,"Publisher",9) == 0))
		{
			strcpy(r.publisher, get_value(str));
			continue;
		}

		//address
		if((strncmp(str,"address", 7) == 0) || (strncmp(str,"Address", 7) == 0) ||
		   (strncmp(str,"location",8) == 0) || (strncmp(str,"Location",8) == 0))
		{
			strcpy(r.address, get_value(str));
			continue;
		}
	}
	
	return r;
}

char * get_bibkey(char str[256])
{
	char * bracket = strstr(str, "{");
	char * comma   = strstr(str, ",");
	*comma = 0;
	
	return bracket + 1;
}

char * get_title(char str[256])
{
	char * open = strstr(str, "{");
	
	int len = strlen(str);

	str[len-2] = 0;			// Cut closing bracket.
	if(str[len-3] == '}')	// If extra closing bracket present, cut it.
		str[len-3] = 0;

	if(open[1] == '{')	// If extra open bracket present, cut it.
		return open + 2;

	return open + 1;
}

char * get_value(char str[256])
{
	char * open = strstr(str, "{");					// Braces is the delimiter.
//	printf("get_value: open = %p\n", open);
	if(open == NULL)	open = strstr(str, "\""); 	// Quatation mark is the delimiter.
//	printf("get_value: open = %p\n", open);

	int len = strlen(str);

	str[len-2] = 0;			// Cut closing bracket '}' or '"'.

//	printf("get_value: str = %s\n", str);
//	printf("get_value: open = %s\n", open);

	return open + 1;		// Cut opening bracket '{' or '"'.
}

int get_five_authors(char str[256], record * r)
{
//	printf("get_five_authors: str = %s\n", str);
	int num = 0;
	char * cur = strstr(str, "{");				// Braces is the delimiter.
	if(cur == NULL)	cur = strstr(str, "\""); 	// Quatation mark is the delimiter.
		
	cur = cur + 1;	// Begining of authors list.
	char * delim;
	
	r->et_al = 0;
	
	while(1)
	{
		delim = strstr(cur, " and ");
		if(delim == NULL)	// Last or single author case.
		{
			if(strncmp(cur, "others", 6) == 0) {r->et_al = 1; break;}
			
			num++;
			read_author(r, num, cur, NULL);
			break;
		}
		
//		printf("\tdelim = %s\n", delim);

		num++;
		read_author(r, num, cur, delim);
		if(num == 5) {r->et_al = 1; break;}	// Do not collect more then 5 authors.
		cur = delim + 5;
	}
	
	return num;
}

void read_author(record * r, int number, char * begin, char * end)
{
	char author[256];
	char lastname[256];
	char initials[256];
	
	// Separate the author as separate string.
	if(end == NULL)						// Last author:
		strncpy(author, begin, 128);	// Copy to the end of string.
	else{
		int len = end-begin;
		strncpy(author, begin, len);
		author[len] = 0;	// End up before delimiter.
	}
	
//	printf("\tauthor = %s\n", author);

	trim(author);
	int len = strlen(author);
	if(author[len-1] == ',') author[len-1] = 0;
	if(author[len-2] == '}') author[len-2] = 0;
	if(author[len-2] == '"') author[len-2] = 0;


	// Parse the lastname and the initials.
	char * comma = strstr(author, ",");
	if(comma != NULL)				// Lastname, A.B.
	{
		int len = comma-author;
		strncpy(lastname, author, len);
		lastname[len] = 0;	// End up before delimiter.
		
		strcpy(initials, comma + 2);
	}
	else							// A.B. Lastname
	{
		char * sp = strstr(author, " ");
		strcpy(lastname, sp+1);

		int len = sp-author;
		strncpy(initials, author, len);
		initials[len] = 0;	// End up before delimiter.
	}
	
	strcpy(r->lastnames[number-1], lastname);
	strcpy(r->initials[number-1], initials);
}

void save_cache(void)
{
	FILE * f = NULL;
	char str[256];
	
	f = fopen(cachefile, "w");
	
	if(f == NULL)
	{
		printf("save_cache: Cannot open file \"%s\" to save cache.\n", cachefile);
		return;
	}	
	
	// Write the number of records at the beginning of cache file.
	sprintf(str, "%d", record_num);
	fputs(str,f);
	
	int written = fwrite(records, sizeof(record), record_num, f);
	fclose(f);
}

int  load_cache(void)
{
	FILE * f = NULL;
	char str[256];
	
	f = fopen(cachefile, "r");
	
	if(f == NULL)
	{
		printf("load_cache: Cannot open file \"%s\" to read cache.\n", cachefile);
		return 0;
	}	
	
	if(fscanf(f, "%d", &record_num) == 0)
	{
		printf("load_cache: Records number is not read.\n");
		return 0;
	}
	
	records = (record *) malloc(record_num * sizeof(record));
	
	int read = fread(records, sizeof(record), record_num, f);
	if(ferror(f) || read < record_num)
		printf("load_cache: Read %d records instead of total %d.\n", read, record_num);

	fclose(f);
	return record_num;
}

char t[256];	// Internal memory block for trim to work.

void trim(char * a)
{
	int len = strlen(a);
	if(len == 0) return;
	
	strcpy(t, a);
	
	int i = 0;
	while(((t[i] == '\r') || (t[i] == '\n') || (t[i] == ' ')) && i < len)	i++;
	
	char * b = t+i;
	len -= i;
	
	int l = strlen(b);
	
	i = 1;
	while(((b[l-i] == '\r') || (b[l-i] == '\n') || (b[l-i] == ' ')) && i < l)	i++;
	
	len -= i - 1;

	strncpy(a, b, len);
	a[len] = 0;
}

void generate_bbl_file(void)
{
	FILE * bbl = NULL;
	FILE * aux = NULL;
	char str[256];
	
	bbl = fopen(bblfile, "w");
	
	if(bbl == NULL)
	{
		printf("generate_bbl_file: Cannot open file \"%s\" to save bbl.\n", bblfile);
		return;
	}

	aux = fopen(auxfile, "r");

	if(aux == NULL)
	{
		printf("generate_bbl_file: Cannot open aux-file \"%s\".\n", auxfile);
		return;
	}
	
	fprintf(bbl, "\\begin{thebibliography}{1}\n\n");
	
	while(fgets(str,256,aux) != NULL)
		if(strncmp(str,"\\citation",9) == 0)
			write_bibitems(bbl,str);

	fprintf(bbl, "\\end{thebibliography}\n");

	fclose(aux);
	fclose(bbl);
}

void write_bibitems(FILE * f, char * s)
{
	char * cur = strstr(s, "{") + 1;	// Begining of texkeys list.
	char * delim;
	char texkey[256];
	int len;
	
	while(1)
	{
		delim = strstr(cur, ",");
		if(delim == NULL)	// Last or single author case.
		{
			len = strlen(cur);
			strncpy(texkey, cur, 256);
			texkey[len-2] = 0;
			write_bibitem(f, texkey);
			break;
		}
		
		len = delim - cur;
		strncpy(texkey, cur, len);
		texkey[len] = 0;
		write_bibitem(f, texkey);

		cur = delim + 1;
	}	
}

void write_bibitem(FILE * f, char * texkey)
{
	record key;
	strcpy(key.bibkey, texkey);

	record * r = (record *)bsearch( &key, records, record_num, sizeof(record), compare_records);
	
	if(r != NULL)	//	Record is found
	{
		if(r->already_used == 0)	// Meet this record first time
		{
			switch(r->type)
			{
				case 1: write_article(f, r); break;
				case 2: write_book   (f, r); break;
				default: fprintf(f, "\\bibitem{%s}\n\n", r->bibkey); break;
			}
			r->already_used = 1;
		}
	}
	else
	{
//		printf("No bib-record for '%s'.\n", texkey);
		fprintf(f, "\\bibitem{%s}\nNo bib-record for '%s'.\n\n", texkey, texkey);
	}
}

void write_article(FILE * f, record * r)
{
	char s[256];
	format_article(s,r);
	fprintf(f, "%s\n", s);
}

void write_book(FILE * f, record * r)
{
	char s[256];
	format_book(s,r);
	fprintf(f, "%s\n", s);
}

void format_article(char s[256], record * r)
{
	int i, l;
	char * c;
	
	sprintf(s, "\\bibitem{%s}\n", r->bibkey);
	l = strlen(r->bibkey) + 11;
	s = s + l;

	if(r->et_al == 0)	// Five or less authors.
	{
		for(i = 0 ; i < r->authors_num ; i++)
		{
			sprintf(s, "%s~%s, ", r->initials[i], r->lastnames[i]);
			l = strlen(r->initials[i]) + 1;
			s = s + l;
			l = strlen(r->lastnames[i]) + 2;
			s = s + l;
		}
	}
	else 		// et al.
	{
		sprintf(s, "%s~%s {\\it{et al.}}, ", r->initials[0], r->lastnames[0]);
		l = strlen(r->initials[0]) + 1;
		s = s + l;
		l = strlen(r->lastnames[0]) + 16;
		s = s + l;
	}
	
	if(strlen(r->collaboration) != 0)
	{
		if(*(s-2) == ',') { s--; *s = 0; s--; *s = ' '; s++; };

		sprintf(s, "(%s Collaboration), ", r->collaboration);
		l = strlen(r->collaboration) + 18;
		s = s + l;
	}
	
//	printf("s = '%s'\n", s-3);

	sprintf(s, "%s {\\bf %s}, %s, (%s).\n", r->journal, r->volume, r->pages, r->year);
}

void format_book(char s[256], record * r)
{
	int i, l;
	char * c;
	
	sprintf(s, "\\bibitem{%s}\n", r->bibkey);
	l = strlen(r->bibkey) + 11;
	s = s + l;

	if(r->et_al == 0)	// Five or less authors.
	{
		for(i = 0 ; i < r->authors_num ; i++)
		{
			sprintf(s, "%s~%s, ", r->initials[i], r->lastnames[i]);
			l = strlen(r->initials[i]) + 1;
			s = s + l;
			l = strlen(r->lastnames[i]) + 2;
			s = s + l;
		}
	}
	else 		// et al.
	{
		sprintf(s, "%s~%s {\\it{et al.}}, ", r->initials[0], r->lastnames[0]);
		l = strlen(r->initials[0]) + 1;
		s = s + l;
		l = strlen(r->lastnames[0]) + 16;
		s = s + l;
	}
	
	sprintf(s, "%s. -- %s: %s, %s p. (%s).\n",
		r->title, r->address, r->publisher, r->pages, r->year);
}
