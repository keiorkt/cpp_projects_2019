# -*- MakeFile -*-

all: mini-os-emulator

run: mini-os-emulator
	./mini-os-emulator

mini-os-emulator: 
	g++ -std=c++11 -o mini-os-emulator

Process.o: Process.cpp
	g++ -std=c++11 -c Process.cpp

.PHONY: clean
clean:
	rm -f *.o mini-os-emulator