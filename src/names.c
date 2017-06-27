/* names.c */

#include <malloc.h> /* realloc, calloc */
#include <string.h> /* memcpy, strlen */
#include <ctype.h> /* isalpha */

#define MAX_LENGTH 21
#define MIN_LENGTH 2

static char** names;
unsigned int numNames = 0;

static char* newName(const char* name) {
	char* _newName = (char*) calloc(MAX_LENGTH, sizeof(char));
	memcpy(_newName, name, MAX_LENGTH -1);
	return _newName;
}

static int _index(const char* name) {
	unsigned int i;
	for ( i=0; i<numNames; i++ ) if ( !strcmp(name, names[i]) ) return i;
	return -1;
}

int badName(const char* name) {
	if ( name == NULL ) return -1;
	char* _name = newName(name);
	unsigned int i;
	for ( i=0; i<strlen(_name); i++ ) if ( !isalpha(_name[i]) ) return -2;
	if ( i<MIN_LENGTH ) return -3;
	if ( !(_index(_name) < 0) ) return -4;
	free(_name);
	return 0;
}

int setName(const char* name) {
	if ( badName(name) ) return badName(name);
	names = (char**) realloc(names, (numNames +1) * sizeof(char*));
	names[numNames] = newName(name);
	return strcmp(name, names[numNames++]) ? -5 : 0;
}

int unsetName(const char* name) {
	char* _name = newName(name);
	if ( _index(_name) < 0 ) {
		free(_name);
		return -1;
	}
	unsigned int i;
	for ( i=_index(_name); i<numNames-1; i++ ) names[i] = names[i+1];
	numNames--;
	free(_name);
	return 0;
}
	
/* end of file */
