/*
 * Complete the Process definitions marked by TODO
 * print() has already been defined for your debugging convenience.
 *
 * You may add your own helper classes, structs, and functions here.
 */

#include "Process.h"

// TODO, You may also use initializer list syntax " : ".
Process::Process(const unsigned int pid, unsigned int execute_time, unsigned int priority) {}

const unsigned int Process::get_pid() const {
	return 0; // TODO
}

unsigned int Process::get_execute_time() const {
	return 0; // TODO
}

unsigned int Process::get_priority() const {
	return 0; // TODO
}

unsigned int Process::get_aging_counter() const {
	return 0; // TODO
}

void Process::print() const {
	cout << "Process ID: " << pid << "\n"
			<< "Execution Time Remaining: " << execute_time << "\n"
			<< "Priority: " << priority << "\n"
			<< "Aging Counter: " << aging_counter << endl;
}

void Process::execute(unsigned int time) {
	// TODO
}

void Process::wait(unsigned int time) {
	// TODO
}

void Process::promote_priority() {
	// TODO
}
