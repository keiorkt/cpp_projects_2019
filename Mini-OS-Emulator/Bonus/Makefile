# -*- MakeFile -*-

all: mini-os-emulator

run: mini-os-emulator
	./mini-os-emulator

doctor: mini-os-emulator
	 ~/Downloads/DrMemory-MacOS-2.2.1-alpha2/bin64/drmemory -- mini-os-emulator

mini-os-emulator: main.o Process.o ProcessNode.o ProcessQueue.o ProcessScheduler.o
	g++ -std=c++11 main.o Process.o ProcessNode.o ProcessQueue.o ProcessScheduler.o -o mini-os-emulator

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Process.o: Process.cpp
	g++ -std=c++11 -c Process.cpp

ProcessNode.o: ProcessNode.cpp
	g++ -std=c++11 -c ProcessNode.cpp

ProcessQueue.o: ProcessQueue.cpp
	g++ -std=c++11 -c ProcessQueue.cpp

ProcessScheduler.o: ProcessScheduler.cpp
	g++ -std=c++11 -c ProcessScheduler.cpp


.PHONY: clean
clean:
	rm -f *.o mini-os-emulator
