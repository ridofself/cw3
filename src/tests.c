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

#include "name.h"

int _name_internals() {
	_assert(!name_internals());
	return 0;
}

int _name_create() {
	_assert(!name_create("Biggs"));
	_assert(name_create("ThisNameIsTooLongItShouldFailToCreate") == -1);
	return 0;
}

int all_tests() {
	test(__assert);

	test(_name_create);
	test(_name_internals);
	return 0;
}

int main(int arc, char** argv) {
	printf("\nResults...");
	int result = all_tests();
	if ( result == 0 ) printf("\tPASSED all tests\n");
	printf("test count:\t%d\n\n", count);
	return result != 0;
}

/* end of file */
