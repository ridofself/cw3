/* user.h */

struct user {	char* name;
		struct acter_group* party;	};
		
int user_create(const char*);

int user_destroy(const char*);

struct user* user_get(const char*);
