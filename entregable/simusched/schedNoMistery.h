#ifndef __SCHED_NO_MISTERY__
#define __SCHED_NO_MISTERY__

#include <vector>
#include <queue>
#include "basesched.h"


class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
        ~SchedNoMistery();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		int nextReadyTask();
		void TaskSwitch(int cpu,const enum Motivo m);
int getNextReadyAndDelete();
	private:
		std::vector<int> tasksReady;
};

#endif
