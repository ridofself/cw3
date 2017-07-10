/* acter.h */

#define ACTER_GROUP_MAX 8 

struct acter
{
	char* name;
};

struct acter_group
{
	struct acter* member[ACTER_GROUP_MAX];
	unsigned int count;
};

int acter_create(const char*);

int acter_destroy(const char*);

struct acter* acter_get(const char*);

struct acter_group* acter_group_new();

int acter_group_assign(struct acter*, struct acter_group*);

int acter_group_resign(struct acter*, struct acter_group*);

/* end of file */
