
#include "iostream"
#include "schedPSJF.h"
#include <stdio.h>

using namespace std;

SchedPSJF::SchedPSJF(vector<int> argn) {
    // SchedPSJF recibe la cantidad de cores.
    for (int i = 0; i < argn[0]; i++) {
        cpu_data_PSJF cpu = cpu_data_PSJF();
        cpu.tareaActual = IDLE_TASK;
        cpu.prioridad = 4;
        cpus.push_back(cpu);
    }
}

SchedPSJF::~SchedPSJF() {
}

void SchedPSJF::load(int pid) {

    //printf("%d\n", tsk_params(pid)->at(0));
    tasksReady[tsk_params(pid)->at(0) - 1].push_back(pid);
}

void SchedPSJF::unblock(int pid) {
    // Uy! unblock!... bueno, ya seguir'a en el próximo tick
}

int SchedPSJF::tick(int cpu, const enum Motivo m) {
    if (m == EXIT) {
        // Si el pid actual terminó, sigue el próximo.
        return getNextReadyAndDiscardActual(cpu);
    } else {
        if (cpus[cpu].tareaActual == IDLE_TASK) {
            return getNextReadyAndDiscardActual(cpu);
        }
        return getNextReady(cpu);
    }
}

int SchedPSJF::getNextReady(int cpu) {
    int prioridad_actual = cpus[cpu].prioridad;
    int result = cpus[cpu].tareaActual;


    int indicePrioridad;
    int indiceDeLista;
    for (int i = 0; i <= prioridad_actual; i++) {
        if (!tasksReady[i].empty()) {
            int laMasCorta = tasksReady[i][0];
            int posicionLaMasCorta = 0;

            // Buscamos la más corta de prioridad i
            for (int j = 0; j < tasksReady[i].size(); j++) {
                if (tsk_params(tasksReady[i][j])->at(1) < tsk_params(laMasCorta)->at(1)) {
                    laMasCorta = tasksReady[i][j];
                    posicionLaMasCorta = j;
                }

            }
            result = laMasCorta;
            indicePrioridad = i;
            indiceDeLista = posicionLaMasCorta;

            break;
        }

    }
//Fijarme si result es mejor que actual. 
    //Si result es mejor que actual --> borro result de tasksReady y la agrego a cpus[cpu] y agrego actual a tasksReady y la saco de cpus[cpu]
    //Si no , no hago nada.

    if (result != cpus[cpu].tareaActual) {
        if (tsk_params(result)->at(0) - 1 < prioridad_actual) {

            switchTareas(cpu, result, indicePrioridad, indiceDeLista);

        } else if (tsk_params(result)->at(0) - 1 == prioridad_actual &&
                   tsk_params(result)->at(1) < tsk_params(cpus[cpu].tareaActual)->at(1)) {
            switchTareas(cpu, result, indicePrioridad, indiceDeLista);
        }
    }
    return cpus[cpu].tareaActual;
}

void SchedPSJF::switchTareas(int cpu, int result, int indicePrioridad,
                             int indiceDeLista) const {//TareaADesalojar es la tarea que esta corriendo en el CPU
    int tareaADesalojar = cpus[cpu].tareaActual;
    //PrioridadADesalojar es la prioridad de la tarea que esta corriendo en el CPU
    int prioridadADesalojar = cpus[cpu].prioridad;
    //Actualizo la informacion del CPU con la nuevatarea result
    cpus[cpu].tareaActual = result;
    cpus[cpu].prioridad = indicePrioridad;
    //elimino result del vector
    tasksReady[indicePrioridad].erase(tasksReady[indicePrioridad].begin() + indiceDeLista);
    //agregar tareaADesalojar al vector
    tasksReady[prioridadADesalojar].push_back(tareaADesalojar);
}


int SchedPSJF::getNextReadyAndDiscardActual(int cpu) {
    int prioridad_actual = cpus[cpu].prioridad;
    int result = IDLE_TASK;


    int indicePrioridad = 4;
    int indiceDeLista;
    for (int i = 0; i <= 4; i++) {
        if (!tasksReady[i].empty()) {
            int laMasCorta = tasksReady[i][0];
            int posicionLaMasCorta = 0;

            // Buscamos la más corta de prioridad i
            for (int j = 0; j < tasksReady[i].size(); j++) {
                if (tsk_params(tasksReady[i][j])->at(1) < tsk_params(laMasCorta)->at(1)) {
                    laMasCorta = tasksReady[i][j];
                    posicionLaMasCorta = j;
                }

            }
            result = laMasCorta;
            indicePrioridad = i;
            indiceDeLista = posicionLaMasCorta;

            break;
        }

    }
    //TareaADesalojar es la tarea que esta corriendo en el CPU
    //Actualizo la informacion del CPU con la nuevatarea result
    cpus[cpu].tareaActual = result;
    cpus[cpu].prioridad = indicePrioridad;

    //elimino result del vector
    if (result != IDLE_TASK) {
        tasksReady[indicePrioridad].erase(tasksReady[indicePrioridad].begin() + indiceDeLista);
    }

    return cpus[cpu].tareaActual;
}
