#ifndef BIBLIO
#define BIBLIO

#include <stdio.h>
#include <string.h>

typedef struct
{
	char bibkey[64];
	int  type;
	char collaboration[256];
	int  authors_num;
	char initials[5][64];
	char lastnames[5][128];
	char title[256];
	char journal[32];
	char year[5];
	char volume[32];
	char pages[32];
	char publisher[64];
	char address[32];
	int  already_used;
	int  et_al;
} record;

extern int record_num;
extern record * records;

extern char auxfile[256];
extern char bibfile[256];
extern char cachefile[512];
extern char bblfile[256];

int compare_records(const void * r1, const void * r2);

void extract_bibfile(void);
void load_records(void);

int  count_bib_records(void);
int  load_bibfile(void);
void sort_db(void);

void save_cache(void);
int  load_cache(void);

void generate_bbl_file(void);

void write_bibitems(FILE * f, char * texkeys);
void write_bibitem (FILE * f, char * texkey);

record load_article(FILE * f, char str[256]);
record load_book   (FILE * f, char str[256]);

void write_article(FILE * f, record * r);
void write_book   (FILE * f, record * r);

void format_article(char buf[256], record * r);
void format_book   (char buf[256], record * r);
				
char * get_bibkey(char str[256]);
char * get_title (char str[256]);
char * get_value (char str[256]);
char * get_bibdata(char str[256]);

int get_five_authors (char str[256], record * r);

void read_author(record * r, int number, char * begin, char * end);

void trim(char * str);

void cleanup(void);

#endif
