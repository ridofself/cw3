/* tests.c */

#define FAIL() printf("\tFAILURE in %s() line %d\n", __func__, __LINE__)
#define _assert(pass) do { if (!(pass)) { FAIL(); return 1; } } while(0)
#define test(func) do { int r=func(); count++; if(r) return r; } while(0)

#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */

int count = 0;

int __assert() {
	_assert("This should pass");
	return 0;
}

#include "names.h"

int _setName() {
	int num = numNames;
	char* name = "Biggs";
	_assert(!setName(name)); /* no errors setting name */
	_assert(numNames == num +1);
	_assert(badName(name) == -4); /* name is being used */
	unsetName(name);
	return 0;
}

int _unsetName() {
	int num = numNames;
	char* name = "Wedge";
	setName(name);
	printf("%d\n", unsetName(name)); /* PROBLEM: used name == bad name */
	_assert(!unsetName(name)); /* no errors unsetting name */
	_assert(!badName(name)); /* name is no longer being used */
	char* unusedName = "Biggs";
	_assert(unsetName(unusedName) == -1); /* no such name to unset */
	_assert(numNames == num);
	char* xName = "$$ 112\t potential overflow!!! do not strcmp!";
	_assert(unsetName(xName) == -1);
	return 0;
}

int _badName() {
	_assert(setName(NULL) == -1);
	_assert(setName("un5@n!t@ry\n n@m3") == -2);
	_assert(setName("") == -3);
	char* dupName = "GeorgeCloney";
	setName(dupName);
	_assert(setName(dupName) == -4);
	_assert(setName("thisNameIsveryLongItShouldTriggerAnError") == -5);
	return 0;
}

int all_tests() {
	test(__assert);

	test(_setName);
	test(_unsetName);
	test(_badName);

	return 0;
}

int main(int arc, char** argv) {
	printf("\nResults...");
	int result = all_tests();
	if ( result == 0 ) printf("\tPASSED all tests\n");
	printf("Tests run:\t%d\n\n", count);
	return result != 0;
}

/* end of file */
