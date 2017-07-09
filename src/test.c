/* test.c */

#include "test.h" /* _assert, test, FAIL */
#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include <malloc.h> /* free */

int count = 0;

int __assert() {
	_assert("This should pass");
	return 0; }

#include "name.h"

int _name_create() {
	char* name = "Biggs";
	_assert(!name_create(name)); /* no errors expected */
	_assert(name_create(NULL) == -1);
	_assert(name_create("") == -2);
	_assert(name_create("ThisNameIsTooLongItShouldFailToCreate") == -3);
	_assert(name_create("ill3g@l ch@r \name") == -4);
	_assert(name_create(name) == -5); /*duplicate name */
	name_destroy(name);
	char * nameWithSpaces = "Sergeant Biggs";
	_assert(!name_create(nameWithSpaces));
	name_destroy(nameWithSpaces);
	return 0; }

int _name_destroy() {
	char* name = "Wedge";
	_assert(!name_create(name));
	_assert(!name_destroy(name)); /* no errors expected */
	_assert(name_destroy(name) == -1); /* already destroyed */
	_assert(name_destroy("Vicks") == -1); /* does not exist either */
	_assert(name_destroy(NULL) == -1);
	return 0; }

int _name_get() {
	_assert(name_get(NULL) == NULL);
	char* name = "Piere";
	name_create(name);
	_assert(!strcmp(name, name_get(name))); /* no errors expected */
	name_destroy(name);
	_assert(name_get(name) == NULL); /* no longer exists */
	return 0; }

int _name_change() {
	char* oldName = "Gandalf The Grey";
	char * newName = "Gandalf The White";
	name_create(oldName);
	_assert(name_change(NULL, newName) == -6); 
	_assert(name_change(oldName, NULL) == -1);
	_assert(!name_change(oldName, newName)); /* no errors expected */
	_assert(name_destroy(oldName) == -1); /* no longer exists */
	_assert(!name_destroy(newName)); 
	return 0; }

#include "acter.h"

int _acter_create() {
	char* name = "Cloud";
	_assert(!acter_create(name)); /* no errors expected */
	_assert(acter_create(name) == -5); /* acter name already exists */
	acter_destroy(name);
	return 0; }

int _acter_destroy() {
	char* name = "Aeres";
	acter_create(name);
	_assert(acter_destroy(NULL) == -1);
	_assert(!acter_destroy(name));
	_assert(acter_destroy(name) == -2);
	name = "not an acter";
	name_create(name);
	_assert(acter_create(name) == -5);
	_assert(acter_destroy(name) == -3);
	name_destroy(name);
	return 0; }

int _acter_get(){
	_assert(acter_get(NULL) == NULL);
	char* name = "Barret";
	acter_create(name);
	_assert(!strcmp(name, acter_get(name)->name)); /* no errors expected */
	acter_destroy(name);
	_assert(acter_get(name) == NULL);
	return 0; }

int _acter_group_resign() {
	struct acter_group* group = acter_group_new();
	char* name = "RED XIII";
	char* name2 = "Tifa";
	acter_create(name);
	acter_create(name2);
	_assert(!acter_group_assign(group, acter_get(name)));
	_assert(!acter_group_assign(group, acter_get(name2)));
	_assert(!acter_group_resign(group, acter_get(name)));
	_assert(acter_group_resign(group, acter_get(name)) == -1);
	acter_destroy(name);
	acter_destroy(name2);
	free(group);
	return 0; }

#include "user.h"

int _user_create() {
	_assert(user_create(NULL) == -1);
	char* name = "Trinity";
	_assert(!user_create(name)); /* no errors expected */
	_assert(user_create(name) == -5); /* duplicate user name */
	user_destroy(name);
	return 0; }

int _user_destroy() {
	char* name = "Mr Anderson";
	user_create(name);
	_assert(user_destroy(NULL) == -1);
	_assert(!user_destroy(name)); /* no errors expected */
	_assert(user_destroy(name) == -2); /* no such user */
	_assert(name_get(name) == NULL);
	user_create(name);
	char* newName = "Neo";
	name_change(name, newName);
	_assert(user_destroy(name) == -2);
	_assert(!user_destroy(newName));
	name = "not a user name";
	name_create(name);
	_assert(user_destroy(name) == -3); /* name is not a user name */
	name_destroy(name);
	return 0; }

int _user_get() {
	_assert(user_get(NULL) == NULL);
	char* name = "Morpheus";
	user_create(name);
	_assert(!strcmp(name, user_get(name)->name)); /* no errors expected */
	user_destroy(name);
	_assert(user_get(name) == NULL);
	return 0; }

int user_party_assign() {
	char* userName = "Patrick Stewart";
	user_create(userName);
	struct user* newUser = user_get(userName);
	char* name = "RED XIII";
	char* name2 = "Tifa";
	acter_create(name);
	acter_create(name2);
	_assert(!acter_group_assign(newUser->party, acter_get(name)));
	_assert(!acter_group_assign(newUser->party, acter_get(name2)));
	_assert(!acter_group_resign(newUser->party, acter_get(name)));
	_assert(acter_group_resign(newUser->party, acter_get(name)) == -1);
	acter_destroy(name);
	acter_destroy(name2);
	user_destroy(userName);
	return 0; }

int all_tests() {
	test(__assert);

	test(_name_create);
	test(_name_destroy);
	test(_name_get);
	test(_name_change);

	test(_acter_create);
	test(_acter_destroy);
	test(_acter_get);
	test(_acter_group_resign);

	test(_user_create);
	test(_user_destroy);
	test(_user_get);
	test(user_party_assign);
	return 0; }

int main(int arc, char** argv) {
	printf("\nResults...");
	int result = all_tests();
	if ( result == 0 ) printf("\tPASSED all tests\n");
	printf("test count:\t%d\n\n", count);
	return result != 0; }

/* end of file */
