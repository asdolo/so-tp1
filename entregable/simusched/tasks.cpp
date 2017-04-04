#include "tasks.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) { // params: n, bmin, bmax, ...
	for(int i = 0; i < (int)params[0]; i++) {
		uso_IO(pid,randomRange(params[1],params[2]));
	}
}

void TaskPajarillo(int pid, vector<int> params) { // params: cantidad_repeticiones, tiempo_cpu, tiempo_bloqueo, ...
	for(int i = 0; i < (int)params[0]; i++) {
		uso_CPU(pid, (int)params[1]);
		uso_IO(pid,(int)params[2]);
	}
}

int randomRange(int min, int max)
{
	//return (int)(((double)(rand()/RAND_MAX)*(max-min)) + min);
	return (int) ((double)(((double)rand())/((double)(RAND_MAX)))*(max-min) + min);
}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskPajarillo, 3);

}
