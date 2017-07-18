/* agent_stat.h */

struct agent_stat
{
	float fat; /* amount of body fat, does not include water content */
	float water; /* total hydration including water found in fat */
	float grain; /* remaining tissue weight minus water and fat */
};

float agent_stat_weight(struct agent_stat*);
float agent_stat_thirst(struct agent_stat*);
float agent_stat_hydration(struct agent_stat*);
float agent_stat_water_loss(struct agent_stat*);
float agent_stat_water_sweat(struct agent_stat*);

