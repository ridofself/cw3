/* agent.h */

#include "agent_stat.h" /* struct agent_stat */

#define AGENT_TEAM_MAX 8 

struct agent
{
	char* name;
	struct agent_stat* stat;
};

struct agent_team
{
	struct agent* member[AGENT_TEAM_MAX];
	unsigned int count;
};

int agent_create(const char*);

int agent_destroy(const char*);

struct agent* agent_get(const char*);

struct agent_team* agent_team_new();

int agent_team_assign(char* agentName, char* userName);

int agent_team_resign(char* agentName, char* userName);

/* end of file */
