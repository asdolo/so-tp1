
#include "iostream"
#include "schedPSJF.h"
#include <stdio.h>

using namespace std;

SchedPSJF::SchedPSJF(vector<int> argn) {
    // SchedPSJF recibe la cantidad de cores.
    for (int i = 0; i < argn[0]; i++){
        cpu_data_PSJF cpu = cpu_data_PSJF();
        cpu.tareaActual = IDLE_TASK;
        cpu.prioridad = 4;
        cpus.push_back(cpu);
    }   
}

SchedPSJF::~SchedPSJF() {
}

void SchedPSJF::load(int pid) {
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
        //El motivo es un tick
        if(cpus[cpu].tareaActual==IDLE_TASK){
            //La tarea actual es la IDLE me fijo si hay alguna tarea a ejecutar
            return getNextReadyAndDiscardActual(cpu);
}
    //Estoy ejecutando una tarea, pero debo fijarme si hay alguna con mayor prioridad o misma prioridad y mas corta que la actual
        return getNextReady(cpu);
    }
}

int SchedPSJF::getNextReady(int cpu){

    int prioridad_actual = cpus[cpu].prioridad;
    int result = cpus[cpu].tareaActual;
    int indicePrioridad;
    int indiceDeLista;

    //Busco tareas menores o iguales que la prioridad de la tarea actual
    for (int i = 0; i <= prioridad_actual; i++)
    {
        //Me fijo si hay alguna tarea con la prioridad i
        if(!tasksReady[i].empty())
        {
            int laMasCorta=tasksReady[i][0];
            int posicionLaMasCorta=0;

            // Buscamos la más corta de prioridad i
            for (unsigned int j = 0; j < tasksReady[i].size(); j++)
            {
                if (tsk_params(tasksReady[i][j])->at(1) < tsk_params(laMasCorta)->at(1))
                {
                    laMasCorta = tasksReady[i][j];
                    posicionLaMasCorta = j;
                }
                
            }
            //Si ya habia algun vector no vacio entonces aqui va a estar la tarea mas prioritaria y mas corta de las ready, ya que recorro busacando desde prioridad 0 hasta prioridad actual.
            result=laMasCorta;
            indicePrioridad=i;
            indiceDeLista=posicionLaMasCorta;

            break;
        }

    }   
//Me fijo si result es mejor que actual. 
    //Si result es mejor que actual --> borro result de tasksReady y la agrego a cpus[cpu] y agrego la tarea que estaba siendo ejecutada (actual) a tasksReady 


    if(result!=cpus[cpu].tareaActual){
    if (tsk_params(result)->at(0) - 1 < prioridad_actual){ 

        //TareaADesalojar es la tarea que esta corriendo en el CPU
        int tareaADesalojar= cpus[cpu].tareaActual;
        //PrioridadADesalojar es la prioridad de la tarea que esta corriendo en el CPU
        int prioridadADesalojar= cpus[cpu].prioridad;
        if (--prioridadADesalojar<0)
        {
            prioridadADesalojar=0;
        }
        //Actualizo la informacion del CPU con la nuevatarea result
        cpus[cpu].tareaActual=result;
        cpus[cpu].prioridad = indicePrioridad;

        //elimino result del vector
        tasksReady[indicePrioridad].erase(tasksReady[indicePrioridad].begin() + indiceDeLista);
        //agregar tareaADesalojar al vector
        tasksReady[prioridadADesalojar].push_back(tareaADesalojar);

    }else if(tsk_params(result)->at(0) - 1 == prioridad_actual && tsk_params(result)->at(1)<tsk_params(cpus[cpu].tareaActual)->at(1))
    {
        //TareaADesalojar es la tarea que esta corriendo en el CPU
        int tareaADesalojar= cpus[cpu].tareaActual;
        int prioridadADesalojar= cpus[cpu].prioridad;
        if (--prioridadADesalojar<0)
        {
            prioridadADesalojar=0;
        }
        cpus[cpu].tareaActual=result;
        cpus[cpu].prioridad = indicePrioridad;
        //eliminar result del vector
        tasksReady[indicePrioridad].erase(tasksReady[indicePrioridad].begin() + indiceDeLista);
        //agregar tareaADesalojar al vector
        tasksReady[prioridadADesalojar].push_back(tareaADesalojar);
    }
    }
    return cpus[cpu].tareaActual;
}



int SchedPSJF::getNextReadyAndDiscardActual(int cpu){
    
    int result = IDLE_TASK;
    int indicePrioridad=4;
    int indiceDeLista;
        //Busco la tarea con mayor prioridad
    for (int i = 0; i <= 4; i++)
    {
        if(!tasksReady[i].empty())
        {
            int laMasCorta=tasksReady[i][0];
            int posicionLaMasCorta=0;

            // Buscamos la más corta de prioridad i
            for (unsigned int j = 0; j < tasksReady[i].size(); j++)
            {
                if (tsk_params(tasksReady[i][j])->at(1) < tsk_params(laMasCorta)->at(1))
                {
                    laMasCorta = tasksReady[i][j];
                    posicionLaMasCorta = j;
                }
                
            }
    //Si ya habia algun vector no vacio entonces aqui va a estar la tarea mas prioritaria y mas corta de las ready, ya que recorro busacando desde prioridad 0 hasta prioridad actual.
            result=laMasCorta;
            indicePrioridad=i;
            indiceDeLista=posicionLaMasCorta;

            break;
        }

    }   
        //TareaADesalojar es la tarea que esta corriendo en el CPU
        //Actualizo la informacion del CPU con la nuevatarea result
        cpus[cpu].tareaActual=result;
        cpus[cpu].prioridad = indicePrioridad;

        //Elimino result del vector. Si es la IDLE no la elimino porque nunca se guarda en el vector.
        if(result!=IDLE_TASK){
            tasksReady[indicePrioridad].erase(tasksReady[indicePrioridad].begin() + indiceDeLista);
        }

    return cpus[cpu].tareaActual;
}
