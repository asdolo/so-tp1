
#include "iostream"
#include "schedNoMistery.h"

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	// FCFS recibe la cantidad de cores.
}

SchedNoMistery::~SchedNoMistery() {
}

void SchedNoMistery::load(int pid) {
	tasksReady.push_back(pid); // llegó una tarea nueva
//	cerr << "Cargando tarea de primer parametro " << (*tsk_params(pid))[0];
}

void SchedNoMistery::unblock(int pid) {
	// Uy! unblock!... bueno, ya seguir'a en el próximo tick
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (tasksReady.empty()) return IDLE_TASK;
		else {
			return getNextReadyAndDelete();
		}
	} else {
		// Siempre sigue el pid actual mientras no termine.
		if (current_pid(cpu) == IDLE_TASK && !tasksReady.empty()) {
			return getNextReadyAndDelete();
		} else {
			return current_pid(cpu);
		}
	}
}

int SchedNoMistery::getNextReadyAndDelete(){
	unsigned int i;
	int tareaMasCorta = tasksReady[0];
	int indiceTareaMasCorta=0;
	for (i = 1; i < tasksReady.size(); i++)
	{
		if (tsk_params(tasksReady[i])[0] < tsk_params(tareaMasCorta)[0])
		{
			tareaMasCorta = tasksReady[i];
			indiceTareaMasCorta=i;
		}
	}
	tasksReady.erase(tasksReady.begin()+indiceTareaMasCorta);
	return tareaMasCorta;

}
