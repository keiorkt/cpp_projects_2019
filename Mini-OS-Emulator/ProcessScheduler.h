/*
 * You may add your own helper classes, structs, and functions here.
 * However, do NOT modify the existing ProcessScheduler class declaration.
 */

#ifndef PROCESSSCHEDULER_H_
#define PROCESSSCHEDULER_H_

#include <iostream>
using std::cout;
using std::endl;
using std::to_string;

#include "ProcessQueue.h"

class ProcessScheduler {
public:
	ProcessScheduler(const unsigned int quantum_threshold, const unsigned int max_priority, const unsigned int aging_threshold);
	~ProcessScheduler();

	void print() const; // Print all the processes in ProcessScheduler.
	bool has_current_process() const; // Check whether we have a currently executing Process.
	void add_process(unsigned int execute_time, unsigned int priority); // Add a process to ProcessScheduler.
	void simulate(unsigned int time); // Run the simulation for the specified amount of time.

private:
	const unsigned int quantum_threshold{0}; // Maximum uninterrupted execution time that the current process can execute, then have to go back to the queue. Disabled if set to 0.
	const unsigned int max_priority{0}; // Priority from 0 to max_priority inclusive. Higher values means higher priority. Purely Round-Robin Scheduling if set to 0.
	const unsigned int aging_threshold{0}; // Process increase their priority by one (aging) after they have waited for this long. Disables aging if set to 0.

	unsigned int quantum_counter{0}; // Keeps track of the current running quantum. Resets whenever a different process gets to execute for whatever reason.
	unsigned int next_pid{0}; // Increments by 1 for every new process. No need to decrement, we will loop back to zero after passing the maximum value.

	Process* current_process{nullptr}; // The currently executing Process. nullptr means no Process is currently executing.
	ProcessQueue* priority_queues{nullptr}; // Each queue is in charge of one priority level, so there are "max_priority + 1" queues in total.
};

#endif /* PROCESSSCHEDULER_H_ */
