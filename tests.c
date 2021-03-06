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
	char* name = "Biggs";
	_assert(!setName(name)); /* no errors setting name */
	_assert(usedName(name)); /* should return true (1) */
	return 0;
}

int _bad_name() {
	_assert(setName(NULL) == -1);
	_assert(setName("un5@n!t@ry\n n@m3") == -2);
	_assert(setName("") == -3);
	return 0;
}

int all_tests() {
	test(__assert);

	test(_setName);
	test(_bad_name);
	return 0;
}

int main(int arc, char** argv) {
	printf("\nResults...");
	int result = all_tests();
	if ( result == 0 ) printf("\tPASSED all tests\n");
	printf("Tests ran:\t%d\n\n", count);
	return result != 0;
}

/* end of file */
