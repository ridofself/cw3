/* name.c */

#include <string.h> /* strcmp, memcpy */
#include <malloc.h> /* malloc */
#define NAME_LENGTH_MAX 21

static char* name_stored(const char* name) {
	char* copiedName = (char*) malloc(NAME_LENGTH_MAX * sizeof (char));
	memcpy(copiedName, name, NAME_LENGTH_MAX);
	if ( copiedName && !strcmp(copiedName, name) ) return copiedName;
	return NULL;
}

int name_create(const char* name) {
	if ( name_stored(name) && !strcmp(name, name_stored(name)) ) return 0;
	return -1;
}

int name_internals() {
	return 0;
}

/* end of file */
