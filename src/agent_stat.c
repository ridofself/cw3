/* agent_stat.c */

#include "agent.h" /* struct agent, agent_get */

float agent_stat_weight(const char* name)
{
	return	agent_get(name)->stat->fat +
		agent_get(name)->stat->water +
		agent_get(name)->stat->grain;
}
