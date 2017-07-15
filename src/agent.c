/* agent.c */

#include <malloc.h> /* malloc */
#include <string.h> /* strcmp */
#include "name.h" /* name_create */
#include "agent.h" /* struct agent */
#include "user.h" /* user_get */

static struct agent** agent_list;
static unsigned int agent_count = 0;

int agent_create(const char* name)
{
	if ( name_create(name) ) return name_create(name);

	struct agent* newAgent = (struct agent*) malloc(sizeof (struct agent));
	newAgent->name = name_get(name);
	newAgent->stat = malloc(sizeof (struct agent_stat));
	agent_list = (struct agent**)
		realloc(agent_list, (agent_count +1) * sizeof (struct agent*));
	agent_list[agent_count++] = newAgent;
	return 0;
}

int agent_destroy(const char* name) /* leave dangling pointer at user->team */
{
	if ( !name ) return -1;

	if ( name_get(name) == NULL ) return -2; /* no such name */

	int i;
	for ( i=0; i<agent_count; i++ )
		if ( !strcmp(agent_list[i]->name, name) )
		{
			name_destroy(name);
			free(agent_list[i]->stat);
			free(agent_list[i]);
			for ( ; i<agent_count-1; i++ )
				agent_list[i] = agent_list[i+1];
			agent_count--;
			return 0;
		}

	return -3; /* name exists but is not an agent name */
}

struct agent* agent_get(const char* name)
{
	if ( !name ) return NULL;

	int i;
	for ( i=0; i<agent_count; i++ )
		if ( !strcmp(agent_list[i]->name, name) )
			return agent_list[i];

	return NULL; /* no such agent name */
}

struct agent_team* agent_team_new()
{
	struct agent_team* newGroup = malloc(sizeof (struct agent_team));
	newGroup->count = 0;
	int i;
	for ( i=0; i<AGENT_TEAM_MAX; i++ ) newGroup->member[i] = NULL;
	return newGroup;
}

int agent_team_assign(char* agentName, char* userName)
{
	if ( agent_get(agentName) == NULL ) return -1;
	if ( user_get(userName) == NULL ) return -2;

	struct agent_team* team = user_get(userName)->team;
	if ( team->count >= AGENT_TEAM_MAX ) return -3; /* team full */

	team->member[team->count++] = agent_get(agentName);
	return 0;
}

int agent_team_resign(char* agentName, char* userName)
{
	if ( agent_get(agentName) == NULL ) return -1;
	if ( user_get(userName) == NULL ) return -2;

	struct agent_team* team = user_get(userName)->team;

	int i;
	for ( i=0; i<team->count; i++ )
		if ( team->member[i] == agent_get(agentName) )
		{
			for ( ; i<team->count-1; i++ )
				team->member[i] = team->member[i+1];
			team->count--;
			team->member[team->count] = NULL;
			
			return 0;
		}

	return -3; /* agent is not a member of user->team */
}

/* end of file */
