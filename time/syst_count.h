/* TODO: Put info */

#ifndef __SYST_COUNT_H__
#define __SYST_COUNT_H__

#include <inttypes.h>

typedef struct {
	int cpu;
	int group;
	uint64_t value;
	uint64_t delta;
	char * event_name;
	double scale_ratio;
	uint64_t enabled_time;
	uint64_t running_time;
	char *	cgroup_name;
} counter_struct;
	
extern void set_options(int argc, char **argv);
extern void init(void);
extern void terminate(void);
extern void start_cpu(int c);
extern void stop_cpu(int c);

/* Returns also NULL on error */
extern counter_struct * read_cpu(int c);

#endif