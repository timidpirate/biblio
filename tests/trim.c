#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../src/biblio.h"

void main()
{
	char a[256];
	
	strcpy(a,"");
	trim(a);
	if(strcmp(a, "") != 0)
		{ printf("Test failed! (input empty string, output expected '' but was '%s' read)\n", a); return; }

	strcpy(a,"   ");
	trim(a);
	if(strcmp(a, "") != 0)
		{ printf("Test failed! (expected '' but was '%s' read)\n", a); return; }

	strcpy(a,"text1");
	trim(a);
	if(strcmp(a, "text1") != 0)
		{ printf("Test failed! (expected 'text1' but was '%s' read)\n", a); return; }
	
	strcpy(a,"  \n text2");
	trim(a);
	if(strcmp(a, "text2") != 0)
		{ printf("Test failed! (expected 'text2' but was '%s' read)\n", a); return; }

	strcpy(a,"text3 \n\n  ");
	trim(a);
	if(strcmp(a, "text3") != 0)
		{ printf("Test failed! (expected 'text3' but was '%s' read)\n", a); return; }

	strcpy(a,"  \ntext4 \n \n ");
	trim(a);
	if(strcmp(a, "text4") != 0)
		{ printf("Test failed! (expected 'text4' but was '%s' read)\n", a); return; }

	printf("Test passed.\n");
}
