/*
 * You may add your own helper classes, structs, and functions here.
 * However, do NOT modify the existing Process class declaration.
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
using std::cout;
using std::endl;

class Process {
public:
	Process(const unsigned int pid, unsigned int execute_time, unsigned int priority);

	const unsigned int get_pid() const; // Get (but cannot modify) Process pid.
	unsigned int get_execute_time() const; // Get (but cannot modify) Process execution time remaining.
	unsigned int get_priority() const; // Get (but cannot modify) Process current priority.
	unsigned int get_aging_counter() const; // Get (but cannot modify) Process current aging counter.

	void print() const; // Print Process info.
	void execute(unsigned int time); // Simulate execution of Process.
	void wait(unsigned int time); // Simulate waiting of Process in the queue.
	void promote_priority(); // Increase Process priority by 1.
	void reset_aging_counter(); // set aging counter to 0

private:
	const unsigned int pid{0}; // Process ID.
	unsigned int execute_time{0}; // Execution Time remaining for Process.
	unsigned int priority{0}; // Current Priority level of Process. Note that larger value is higher priority.
	unsigned int aging_counter{0}; // Counter to keep track of time-elapsed while Process is waiting. Resets whenever aging occurs or Process gets to execute.
};

#endif /* PROCESS_H_ */
