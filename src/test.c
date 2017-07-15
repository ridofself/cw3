/* test.c */

#include "test.h" /* _assert, test, FAIL */
#include <stdio.h>  /* printf */
#include <string.h> /* strcmp, strupr */
#include <malloc.h> /* free */

int count = 0;

int __assert() 
{
	_assert("This should pass");
	return 0;
}

#include "name.h"

char rName[NAME_LENGTH_MAX];
char* randName()
{
	name_random(rName, NAME_LENGTH_MAX);
	return rName;
}

int _name_create()
{
	char* name = randName();
	_assert(!name_create(name)); /* no errors expected */
	_assert(name_create(NULL) == -1);
	_assert(name_create("") == -2);

	char nameTooLong[NAME_LENGTH_MAX+1];
	name_random(nameTooLong, NAME_LENGTH_MAX+1);
	_assert(name_create(nameTooLong) == -3);

	_assert(name_create("ill3g@l ch@r \name") == -4);
	_assert(name_create(name) == -5); /*duplicate name */
	name_destroy(name);
	return 0;
}

int _name_destroy()
{
	char* name = randName();
	name_create(name);
	_assert(!name_destroy(name)); /* no errors expected */
	_assert(name_destroy(name) == -1); /* already destroyed */
	_assert(name_destroy(randName()) == -1); /* does not exist either */
	_assert(name_destroy(NULL) == -1);
	return 0;
}

int _name_get()
{
	_assert(name_get(NULL) == NULL);
	char* name = randName();
	name_create(name);
	_assert(!strcmp(name, name_get(name))); /* names should compare */
	name_destroy(name);
	_assert(name_get(name) == NULL); /* no longer exists */
	return 0;
}

int _name_change()
{
	char* oldName = "To Be Changed";
	name_create(oldName);
	char* newName = randName(); 
	_assert(name_change(NULL, newName) == -6); 
	_assert(name_change(oldName, NULL) == -1);
	_assert(!name_change(oldName, newName)); /* no errors expected */
	_assert(name_destroy(oldName) == -1); /* no such name in list */
	name_destroy(newName); 
	return 0;
}

#include "agent.h"

int _agent_create()
{
	char* name = randName();
	_assert(!agent_create(name)); /* no errors expected */
	_assert(agent_create(name) == -5); /* agent name already exists */
	agent_destroy(name);
	return 0;
}

int _agent_destroy()
{
	char* name = randName();
	agent_create(name);
	_assert(agent_destroy(NULL) == -1);
	_assert(!agent_destroy(name));
	_assert(agent_destroy(name) == -2);
	name = "not an agent";
	name_create(name);
	_assert(agent_create(name) == -5);
	_assert(agent_destroy(name) == -3);
	name_destroy(name);
	return 0;
}

int _agent_get()
{
	_assert(agent_get(NULL) == NULL);
	char* name = randName();
	agent_create(name);
	_assert(!strcmp(name, agent_get(name)->name)); /* no errors expected */
	agent_destroy(name);
	_assert(agent_get(name) == NULL);
	return 0;
}

#include "user.h"

int _user_create()
{
	_assert(user_create(NULL) == -1);
	char* name = randName();
	_assert(!user_create(name)); /* no errors expected */
	_assert(user_create(name) == -5); /* duplicate user name */
	user_destroy(name);
	return 0;
}

int _user_destroy()
{
	char* name = "To Be Changed"; 
	user_create(name);
	_assert(user_destroy(NULL) == -1);
	_assert(!user_destroy(name)); /* no errors expected */
	_assert(user_destroy(name) == -2); /* no such user */
	_assert(name_get(name) == NULL);
	user_create(name);
	char* newName = randName();
	name_change(name, newName);
	_assert(user_destroy(name) == -2);
	_assert(!user_destroy(newName));
	name = "not a user name";
	name_create(name);
	_assert(user_destroy(name) == -3); /* name is not a user name */
	name_destroy(name);
	return 0;
}

int _user_get()
{
	_assert(user_get(NULL) == NULL);
	char* name = randName();
	user_create(name);
	_assert(!strcmp(name, user_get(name)->name)); /* no errors expected */
	user_destroy(name);
	_assert(user_get(name) == NULL);
	return 0;
}

int user_team_assign()
{
	char* userName = randName();
	user_create(userName);
	char* agentName = "rands agent";
	agent_create(agentName);
	_assert(agent_team_assign(NULL, userName) == -1);
	_assert(agent_team_assign(agentName, NULL) == -2);
	_assert(!agent_team_assign(agentName, userName));
	_assert(agent_team_resign(NULL, userName) == -1);
	_assert(agent_team_resign(agentName, NULL) == -2);
	_assert(!agent_team_resign(agentName, userName));
	_assert(agent_team_resign(agentName, userName) == -3);
	agent_destroy(agentName);

	int i;
	for ( i=0; i<AGENT_TEAM_MAX; i++ )
	{
		agent_create(agentName);
		agent_team_assign(agentName, userName);
		agent_destroy(agentName); /* does not reduce user->team */
	} 
	agent_create(agentName);
	_assert(agent_team_assign(agentName, userName) == -3); /* team full */

	agent_destroy(agentName);
	user_destroy(userName);
	return 0;
}

/* agent_stat */

int _agent_stat_weight()
{
	char* name = randName();
	agent_create(name);
	agent_get(name)->stat->fat = 23;
	agent_get(name)->stat->water = 68;
	agent_get(name)->stat->grain = 33;
	_assert(agent_stat_weight(name) == 124.0);
	agent_destroy(name);
	return 0;
}

int all_tests()
{
	test(__assert);

	test(_name_create);
	test(_name_destroy);
	test(_name_get);
	test(_name_change);

	test(_agent_create);
	test(_agent_destroy);
	test(_agent_get);

	test(_user_create);
	test(_user_destroy);
	test(_user_get);
	test(user_team_assign);

	test(_agent_stat_weight);
	return 0;
}

int main(int arc, char** argv)
{
	printf("\nResults...");
	int result = all_tests();
	if ( result == 0 ) printf("\tPASSED all tests\n");
	printf("test count:\t%d\n\n", count);
	return result != 0;
}

/* end of file */
