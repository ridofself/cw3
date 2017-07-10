/* acter.c */

#include <malloc.h> /* malloc */
#include <string.h> /* strcmp */
#include "name.h" /* name_create */
#include "acter.h" /* struct acter */


static struct acter** acter_list;
static unsigned int acter_count = 0;


int acter_create(const char* name)
{
	if ( name_create(name) ) return name_create(name);

	struct acter* newActer = (struct acter*) malloc(sizeof (struct acter));
	newActer->name = name_get(name);
	acter_list = (struct acter**)
		realloc(acter_list, (acter_count +1) * sizeof (struct acter*));
	acter_list[acter_count] = newActer;
	acter_count++;
	return 0;
}

int acter_destroy(const char* name)
{
	if ( !name ) return -1;

	if ( name_get(name) == NULL ) return -2; /* no such name */

	int i;
	for ( i=0; i<acter_count; i++ )
	{
		if ( !strcmp(acter_list[i]->name, name) )
		{
			name_destroy(name);
			free(acter_list[i]);
			for ( ; i<acter_count-1; i++ )
			{
				acter_list[i] = acter_list[i+1];
			}
			acter_count--;
			return 0;
		}
	}

	return -3; /* name exists but is not an acter name */
}

struct acter* acter_get(const char* name)
{
	if ( !name ) return NULL;

	int i;
	for ( i=0; i<acter_count; i++ )
	{
		if ( !strcmp(acter_list[i]->name, name) )
		{
			return acter_list[i];
		}
	}

	return NULL; /* no such acter name */
}

struct acter_group* acter_group_new()
{
	struct acter_group* newGroup = malloc(sizeof (struct acter_group));
	newGroup->count = 0;
	int i;
	for ( i=0; i<ACTER_GROUP_MAX; i++ ) newGroup->member[i] = NULL;
	return newGroup;
}

int acter_group_assign(struct acter* acter, struct acter_group* group)
{
	group->member[group->count++] = acter;
	return 0;
}

int acter_group_resign(struct acter* acter, struct acter_group* group)
{
	int i;
	for ( i=0; i<group->count; i++ )
	{
		if ( group->member[i] == acter )
		{
			for ( ; i<group->count-1; i++ )
			{
				group->member[i] = group->member[i+1];
			}
			group->count--;
			group->member[group->count] = NULL;
			return 0;
		}
	}
	return -1; /* no such */
}

/* end of file */
