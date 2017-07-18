/* name.h */

#define NAME_LENGTH_MAX 20

int name_create(const char*);
int name_destroy(const char*);
char* name_get(const char*);
int name_change(const char*, const char*);
void name_random(char*, int);
/* end of file */
