/* user.h */

struct user
{
	char* name;
	struct agent_team* team;
};
		
int user_create(const char*);

int user_destroy(const char*);

struct user* user_get(const char*);

/* end of file */
