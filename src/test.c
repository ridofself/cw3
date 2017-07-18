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


int _name_create()
{
	char* name = "good name";
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
	char* name = "name to be destroyed";
	name_create(name);
	_assert(!name_destroy(name)); /* no errors expected */
	_assert(name_destroy(name) == -1); /* already destroyed */
	_assert(name_destroy("does not exist") == -1);
	_assert(name_destroy(NULL) == -1);
	return 0;
}

int _name_get()
{
	_assert(name_get(NULL) == NULL);
	char* name = "real name";
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
	char* newName = "Changed Name"; 
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
	char* name = "new agent";
	_assert(!agent_create(name)); /* no errors expected */
	_assert(agent_create(name) == -5); /* agent name already exists */
	agent_destroy(name);
	return 0;
}

int _agent_destroy()
{
	char* name = "agent to destroy";
	agent_create(name);
	_assert(agent_destroy(NULL) == -2);
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
	char* name = "real agent";
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
	char* name = "new user";
	_assert(!user_create(name)); /* no errors expected */
	_assert(user_create(name) == -5); /* duplicate user name */
	user_destroy(name);
	return 0;
}

int _user_destroy()
{
	char* name = "old user name"; 
	user_create(name);
	_assert(user_destroy(NULL) == -1);
	_assert(!user_destroy(name)); /* no errors expected */
	_assert(user_destroy(name) == -2); /* no such user */
	_assert(name_get(name) == NULL);
	user_create(name);
	char* newName = "new user name";
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
	char* name = "real user";
	_assert(user_get(name) == NULL); /* not a user yet */
	user_create(name);
	_assert(!strcmp(name, user_get(name)->name)); /* no errors expected */
	user_destroy(name);
	_assert(user_get(name) == NULL);
	return 0;
}

int _agent_team_assign()
{
	char* userName = "user with team";
	char* agentName = "assigned to team";
	_assert(agent_team_assign(agentName, "irrelevant") == -1);
	agent_create(agentName);
	_assert(agent_team_assign(agentName, userName) == -2);
	user_create(userName);
	_assert(!agent_team_assign(agentName, userName));
	_assert(agent_team_assign(agentName, userName) == -4);
	agent_team_resign(agentName, userName);
	agent_destroy(agentName);

	char teamMemberName[NAME_LENGTH_MAX];
	char* agentNames[AGENT_TEAM_MAX];
	int i;
	for ( i=0; i<AGENT_TEAM_MAX; i++ )
	{
		name_random(teamMemberName, NAME_LENGTH_MAX);
		_assert(!agent_create(teamMemberName));
		_assert(!agent_team_assign(teamMemberName, userName));
		agentNames[i] = agent_get(teamMemberName)->name;
	}	
	name_random(teamMemberName, NAME_LENGTH_MAX);
	_assert(!agent_create(teamMemberName));
	_assert(agent_team_assign(teamMemberName, userName) == -3);

	for ( i=0; i<AGENT_TEAM_MAX; i++ )
		agent_destroy(agentNames[i]);
	user_destroy(userName);
	return 0;
}

int _agent_team_resign()
{
	char* userName = "user with agent";
	char* agentName = "assigned to user";
	_assert(agent_team_resign(agentName, "irrelevent") == -1);
	agent_create(agentName);
	_assert(agent_team_resign(agentName, userName) == -2);
	user_create(userName);
	agent_team_assign(agentName, userName);
	_assert(!agent_team_resign(agentName, userName));
	_assert(agent_team_resign(agentName, userName) == -3);
	agent_destroy(agentName);
	return 0;
}

/* agent_stats */

int water_loss_simulation()
{
	char* waterSim = "thirst to death";
	agent_create(waterSim);
	struct agent_stat* stat = agent_get(waterSim)->stat;
	stat->water = 122.0;
	stat->grain = 60.0;
	stat->fat = 20.0;

	int i;
	for ( i=0; i<14401; i++)
	{
		stat->water = stat->water - agent_stat_water_loss(stat);
		if ( i % 1440 == 0 ) printf("day %d: %f\t water: %f \n",
			i/1440, agent_stat_thirst(stat), stat->water);
	}
	
	for ( i=0; i<18721; i++)
	{
		stat->water = stat->water + agent_stat_hydration(stat);
		stat->water = stat->water - agent_stat_water_loss(stat);
		if ( i % 1440 == 0 ) printf("day %d: %f\t water: %f \n",
			i/1440, agent_stat_thirst(stat), stat->water);
	}
 
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

	test(_agent_team_assign);
	test(_agent_team_resign);

	test(water_loss_simulation);
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
