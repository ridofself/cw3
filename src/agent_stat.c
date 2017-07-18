/* agent_stat.c */

#include "agent.h" /* struct agent, agent_get */
#include "name.h" /* name_get */

float agent_stat_weight(struct agent_stat* stat)
{ /* body weight not inlcluding anything carried or worn */
	return	stat->fat + stat->water + stat->grain;
}

float agent_stat_thirst(struct agent_stat* stat)
{ /* checks hydration to determine penalty (if any) due to water deficit */
	float thirst =
		((4.0 * stat->grain ) - (2 * stat->water)) / stat->grain;
	return thirst < 0 ? 0 : thirst; /* max=2*grain wt, min=1.5*grain wt */
}

float agent_stat_hydration(struct agent_stat* stat)
{ /* average amount of water which can be consumed by the minute */
	if ( stat->water < (2 * stat->grain) + (0.1 * stat->fat) )
		return 2 * agent_stat_water_loss(stat);
	return 0;
}

float agent_stat_water_loss(struct agent_stat* stat)
{ /* amount of insensible water loss per minute */
	return ((1.15 - agent_stat_thirst(stat)) * stat->grain) / 14400;
}

float agent_stat_water_sweat(struct agent_stat* stat) 
{ /* potential water loss due to sweat per minute */
	return ((1 - agent_stat_thirst(stat)) * stat->grain) / 1000;
}

float agent_stat_fat_loss(struct agent_stat* stat)
{ /* pounds of fat spent per minute stayin' alive */
	return (stat->grain) / 142200; 
}

float agent_stat_fat_burn(struct agent_stat* stat)
{ /* pounds of fat burned per minute during strenuous exercise, fully rested */
	return stat->grain / 7100;
}
