/* test.h */

#define FAIL() printf("\tFAILURE in %s() line %d\n", __func__, __LINE__)
#define _assert(pass) do { if (!(pass)) { FAIL(); return 1; } } while(0)
#define test(func) do { int r=func(); count++; if(r) return r; } while(0)

/* end of file */
