/* acter.c */

#include <malloc.h> /* malloc */
#include <string.h> /* strcmp */
#include "name.h" /* name_create */

struct acter {	char* name;	};


static struct acter** acter_list;
static unsigned int acter_count = 0;


int acter_create(const char* name) {

	if ( name_create(name) ) return name_create(name);

	struct acter* newActer = (struct acter*) malloc(sizeof (struct acter));
	newActer->name = name_get(name);
	acter_list = (struct acter**)
		realloc(acter_list, (acter_count +1) * sizeof (struct acter*));
	acter_list[acter_count] = newActer;
	acter_count++;
	return 0; }


int acter_destroy(const char* name) {

	if ( !name ) return -1;

	if ( name_get(name) == NULL ) return -2; /* no such name */

	int i;
	for ( i=0; i<acter_count; i++ ) {
		if ( !strcmp(acter_list[i]->name, name) ) {
			name_destroy(name);
			free(acter_list[i]);
			for ( ; i<acter_count-1; i++ ) {
				acter_list[i] = acter_list[i+1]; }
			acter_count--;
			return 0; } }

	return -3; } /* name exists but is not an acter name */


/* end of file */
