/* name.c */

#include <string.h> /* strcmp, strcpy, memcpy */
#include <malloc.h> /* malloc, free */
#include <ctype.h> /* isalpha */
#include <stdlib.h> /* rand */

#include "name.h" /* NAME_LENGTH_MAX */

static char** name_list;
static unsigned int name_count = 0;

static int name_check(const char* name) /* returns 0 if name is valid */
{
	if ( !name ) return -1; /* name is NULL */

	if ( !strcmp("", name) ) return -2; /* name is blank */

	char* copiedName = (char*) malloc(NAME_LENGTH_MAX * sizeof (char));
	memcpy(copiedName, name, NAME_LENGTH_MAX);
	if ( !copiedName || strcmp(name, copiedName) )
	{ 
		free(copiedName);
		return -3; /* no null term within NAME_LENGTH_MAX chars */
	}

	int i;
	for ( i=0; i<strlen(copiedName); i++ )
		if ( !isalpha(copiedName[i]) && copiedName[i] != 32 )
		{
			free(copiedName);
			return -4; /* contains at least one illegal char */
		}

	for ( i=0; i<name_count; i++ )
		if ( !strcmp(name_list[i], copiedName) )
		{
			free(copiedName);
			return -5; /* name is already in use */
		}

	free(copiedName);
	return 0;
}

int name_create(const char* name)
{
	if ( name_check(name) ) return name_check(name);

	char* copiedName = (char*) malloc(NAME_LENGTH_MAX * sizeof (char));
	strcpy(copiedName, name);
	name_list = (char**)realloc(name_list, (name_count+1) * sizeof (char*));
	name_list[name_count] = copiedName;
	name_count++;
	return 0; /* new name stored */
}

int name_destroy(const char* name)
{
	int i;
	for ( i=0; i<=name_count; i++ )
	{
		if ( i == name_count ) return -1; /* no matching name */

		if ( !strcmp(name_list[i], name) )
		{
			free(name_list[i]);
			for ( ; i<name_count-1; i++ )
				name_list[i] = name_list[i+1];
			name_count--;
		}
	}
	return 0; /* name removed from list */
}

char* name_get(const char* name)
{ 
	if( !name ) return NULL;

	int i;
	for ( i=0; i<name_count; i++ )
		if ( !strcmp(name_list[i], name) ) return name_list[i];

	return NULL; /* name does not exist */
}

int name_change(const char* old, const char* new)
{
	if ( name_check(new) ) return name_check(new); /* returns -1 thru -5 */

	if ( name_get(old) == NULL ) return -6; /* no such name */

	strcpy(name_get(old), new);
	return 0;
}

void name_random(char* s, const int len)
{
	static const char alpha[] =
		" ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	int i;
	for ( i=0; i<len; ++i ) 
		s[i] = alpha[rand() % (sizeof (alpha) - 1)];

	s[len] = 0;
}

/* end of file */
