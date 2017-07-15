/* agent_stat.h */

float agent_stat_weight(const char*);

struct agent_stat
{
	float fat; /* amount of body fat, does not include water content */
	float water; /* total hydration including water found in fat */
	float grain; /* remaining tissue weight minus water and fat */
};

