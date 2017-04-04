#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"

struct task_data {
	int pid;
	bool bloqueada;
};

struct cpu_data {
	int tareaActual;
	int quantumsTranscurridos;
	int quamtumsToSwitch;
};


class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::vector<task_data> tasks;
		std::vector<cpu_data> cpus;
};

#endif
