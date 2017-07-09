/* user.c */

#include <malloc.h> /* realloc */
#include "string.h" /* strcmp */
#include "name.h" /* name_create, name_destroy, name_get */
#include "acter.h" /* struct acter */
#include "user.h" /* struct user */


static struct user** user_list;
static unsigned int user_count = 0;


int user_create(const char* name) {
	
	if ( name_create(name) ) return name_create(name);

	struct user* newUser = (struct user*) malloc(sizeof (struct user));
	newUser->name = name_get(name);
	newUser->party = acter_group_new();
	user_list = (struct user**)
		realloc(user_list, (user_count+1) * sizeof (struct user*));
	user_list[user_count] = newUser;
	user_count++;
	return 0; }


int user_destroy(const char* name) {

	if ( !name ) return -1;
	
	if ( name_get(name) == NULL ) return -2; /* no such name */

	int i;
	for ( i=0; i<user_count; i++ ) {
		if ( !strcmp(user_list[i]->name, name) ) {
			name_destroy(name);
			free(user_list[i]);
			for ( ; i<user_count-1; i++ ) {
				user_list[i] = user_list[i+1]; }
			user_count--; 
			return 0; } } /* user destroyed */ 

	return -3; } /* name is not a user name */


struct user* user_get(const char* name) {

	if ( !name ) return NULL; 

	int i;
	for ( i=0; i<user_count; i++ ) {
		if ( !strcmp(user_list[i]->name, name) ) {
			return user_list[i]; } }

	return NULL; } /* no such acter name */


/* end of file */
