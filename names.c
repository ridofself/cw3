/* names.c */

#include <malloc.h> /* realloc, calloc */
#include <string.h> /* memcpy, strlen */
#include <ctype.h> /* isalpha */

#define LENGTH 21 /* max name length including null term */

char** names;
unsigned int numNames = 0;

static char* newName(const char* name) {
	char* _newName = (char*) calloc(LENGTH, sizeof(char));
	memcpy(_newName, name, LENGTH -1);
	return _newName;
}

static int bad(const char* name) {
	if ( name == NULL ) return -1;
	char* _name = newName(name);
	unsigned int i;
	for ( i=0; i<LENGTH; i++ ) if ( !isalpha(_name[i]) ) return -2;
	return 0;
}

int setName(const char* name) {
	if ( bad(name) ) return bad(name);
	names = (char**) realloc(names, (numNames +1) * sizeof(char*));
	names[numNames] = newName(name);
	return strcmp(name, names[numNames++]) ? -7 : 0;
}

static int _index(const char* name) {
	unsigned int i;
	for ( i=0; i<numNames; i++ ) if ( !strcmp(name, names[i]) ) return i;
	return -1;
}

int usedName(char* name) {
	return !(_index(name) < 0);
}
