#ifndef __SCHED_PSJF__
#define __SCHED_PSJF__

#include <vector>
#include <queue>
#include "basesched.h"
struct cpu_data_PSJF
{
	int tareaActual;
	int prioridad;
};

class SchedPSJF : public SchedBase {
	public:
		SchedPSJF(std::vector<int> argn);
        ~SchedPSJF();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		int getNextReady(int cpu);
		int getNextReadyAndDiscardActual(int cpu);
	private:
		std::vector<cpu_data_PSJF> cpus;
		std::vector<int> tasksReady[5];
		std::vector<int> tasksCorriendo;

};

#endif
