#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>
#include <stdio.h>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	for (int i = 1; i <= argn[0]; i++){
		cpu_data cpu = cpu_data();
		cpu.tareaActual = IDLE_TASK;
		cpu.quantumsTranscurridos = 0;
		cpu.quamtumsToSwitch = argn[i];
		cpus.push_back(cpu);

	}	

}

SchedRR::~SchedRR() {
	// No hace falta
}


void SchedRR::load(int pid) {
	tasksReady.push(pid);
}

void SchedRR::unblock(int pid) {
	
	for (unsigned int i = 0; i < tasksBloqueadas.size(); i++)
	{
		int t = tasksBloqueadas.front();
		tasksBloqueadas.pop();
		if (t == pid)
		{
			tasksReady.push(t);
			break;
		}
		else
		{
			tasksBloqueadas.push(t);
		}
	}
}

int SchedRR::tick(int cpu, const enum Motivo m) {

	if (m == EXIT)
	{
		// La tarea terminó
		cpus[cpu].quantumsTranscurridos = 0;		// Reseteamos los quantums transcurridos
		cpus[cpu].tareaActual = nextReadyTask();	// Buscamos la siguiente tarea ready. Si no hay, asignamos IDLE_TASK.
	}
	else if (m == BLOCK)
	{
		// La tarea se bloqueó, la movemos a la cola de tareas bloqueadas y le asignamos la siguiente tarea ready a este core. Si no hay, asignamos IDLE_TASK.
		TaskSwitch(cpu, BLOCK);			
	}
	else if (m == TICK)
	{
		// Pasó un quantum, lo incrementamos
		cpus[cpu].quantumsTranscurridos++;
		if (cpus[cpu].quantumsTranscurridos >= cpus[cpu].quamtumsToSwitch)
		{
			// Pasaron todos los quantum
			TaskSwitch(cpu, TICK);					// Cambio a la siguiente tarea ready. Si no hay, asignamos IDLE_TASK.
		}
		else
		{
			if (cpus[cpu].tareaActual == IDLE_TASK)
			{
				// La tarea actual es IDLE_TASK
				cpus[cpu].quantumsTranscurridos = 0;		// Reseteamos los quantums transcurridos para que vuelva a caer en este caso, si vuelve a ser la idle
				cpus[cpu].tareaActual = nextReadyTask();	// Buscamos (de nuevo) la siguiente tarea ready. Si no hay, de nuevo, asignamos IDLE_TASK.				
			}

		}
	}

	return cpus[cpu].tareaActual;
}

/*
	int SchedRR::nextReadyTask()
	Desencola y devuelve la siguiente tarea en ready. Si no hay tareas en ready, devuelve IDLE_TASK.
*/
int SchedRR::nextReadyTask()
{
	int result = IDLE_TASK;

	if (tasksReady.size() != 0) 
	{
		result = tasksReady.front();
		tasksReady.pop();
	}
	return result;
}

/*
	void SchedRR::TaskSwitch(int cpu)

	Asigna la siguiente tarea ready a ejecutar al cpu pasado por parámetro
	Parámetros: int cpu: cpu en el cual se asignará la siguiente tarea ready
				Motivo m: motivo por el cual se llama a la función
*/
void SchedRR::TaskSwitch(int cpu, const enum Motivo m)
{
	if (m == BLOCK){
		// La tarea anterior se bloqueó
		tasksBloqueadas.push(cpus[cpu].tareaActual);	// La agregamos a la cola de tareas bloqueadas
		cpus[cpu].quantumsTranscurridos = 0;			// Reseteamos los quantums transcurridos, ya que vamos a asignar una nueva tarea a este cpu
		cpus[cpu].tareaActual = nextReadyTask();		// Buscamos la siguiente tarea ready. Si no hay, asignamos IDLE_TASK.
	}
	else if (m == TICK)
	{
		// La tarea cumplió su cantidad de quamtums en este CPU
		if(cpus[cpu].tareaActual!=IDLE_TASK) tasksReady.push(cpus[cpu].tareaActual);			// La agregamos al final de cola de tareas ready
		cpus[cpu].quantumsTranscurridos = 0;			// Reseteamos los quantums transcurridos, ya que vamos a asignar una nueva tarea a este cpu
		cpus[cpu].tareaActual = nextReadyTask();		// Buscamos la siguiente tarea ready. Si no hay, asignamos IDLE_TASK.

	}
}