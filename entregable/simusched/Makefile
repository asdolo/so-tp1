export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_fcfs.o sched_rr.o schedNoMistery.o schedPSJF.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h sched_rr.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)
	rm graficos/*

new: clean all

ejercicio1:
	./simusched loteEj1.tsk 2 0 0 SchedFCFS | python graphsched.py > graficos/ejercicio1.png

ejercicio2:
	./simusched loteEj2.tsk 1 2 0 SchedFCFS | python graphsched.py > graficos/ejercicio2a.png
	./simusched loteEj2.tsk 2 2 0 SchedFCFS | python graphsched.py > graficos/ejercicio2b.png
	./simusched loteEj2.tsk 3 2 0 SchedFCFS | python graphsched.py > graficos/ejercicio2c.png

ejercicio3:
	./simusched loteEj3.tsk 2 2 0 SchedFCFS | python graphsched.py > graficos/ejercicio3a.png
	./simusched loteEj3.tsk 3 2 0 SchedFCFS | python graphsched.py > graficos/ejercicio3b.png

ejercicio4:
	./simusched loteEj4.tsk 2 2 0 SchedRR | python graphsched.py > graficos/ejercicio4.png

ejercicio5:
	./simusched loteEj5a.tsk 2 2 0 SchedMistery | python graphsched.py > graficos/ejercicio5a.png
	./simusched loteEj5b.tsk 1 0 0 SchedMistery | python graphsched.py > graficos/ejercicio5b.png

ejercicio6:
	./simusched loteEj6a.tsk 2 2 0 SchedPSJF | python graphsched.py > graficos/ejercicio6a.png

ejercicio7:
	./simusched loteEj71.tsk 1 1 0 SchedMistery | python graphsched.py > graficos/ej7Mistery1NucleoLote1.png
	./simusched loteEj71.tsk 2 1 0 SchedMistery | python graphsched.py > graficos/ej7Mistery2NucleoLote1.png
	./simusched loteEj71PSJF.tsk 1 1 0 SchedPSJF | python graphsched.py > graficos/ej7PSJF1NucleoLote1.png
	./simusched loteEj71PSJF.tsk 2 1 0 SchedPSJF | python graphsched.py > graficos/ej7PSJF2NucleoLote1.png
	./simusched loteEj71.tsk 1 1 0 SchedRR 5 | python graphsched.py > graficos/ej7RR1NucleoLote1.png
	./simusched loteEj71.tsk 2 1 0 SchedRR 5 5 | python graphsched.py > graficos/ej7RR2NucleoLote1.png
	./simusched loteEj7VideoJuego.tsk 1 1 0 SchedRR 5 | python graphsched.py > graficos/ej7RRLoteVideojuego.png

