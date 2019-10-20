/*
 * Complete the Process definitions marked by TODO
 * print() has already been defined for your debugging convenience.
 *
 * You may add your own helper classes, structs, and functions here.
 */

#include "Process.h"

// TODO, You may also use initializer list syntax " : ".
Process::Process(const unsigned int pid, unsigned int execute_time, unsigned int priority) : pid{pid}, execute_time{execute_time}, priority{priority} {}

const unsigned int Process::get_pid() const {
	return this->pid;
}

unsigned int Process::get_execute_time() const {
	return this->execute_time;
}

unsigned int Process::get_priority() const {
	return this->priority;
}

unsigned int Process::get_aging_counter() const {
	return this->aging_counter;
}

void Process::print() const {
	cout << "Process ID: " << pid << "\n"
			<< "Execution Time Remaining: " << execute_time << "\n"
			<< "Priority: " << priority << "\n"
			<< "Aging Counter: " << aging_counter << endl;
}

void Process::execute(unsigned int time) {
	this->execute_time = (this->get_execute_time() - time <= 0) ? 0 : (this->get_execute_time() - time);
}

void Process::wait(unsigned int time) {
	this->aging_counter += time;
}

void Process::promote_priority() {
	++this->priority;
}
