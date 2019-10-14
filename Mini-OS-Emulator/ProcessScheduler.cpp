/*
 * Complete the ProcessScheduler definitions marked by TODO
 * print() has already been defined for your debugging convenience.
 *
 * You may add your own helper classes, structs, and functions here.
 */

#include "ProcessScheduler.h"

// TODO, You may also use initializer list syntax " : ".
ProcessScheduler::ProcessScheduler(const unsigned int quantum_threshold, const unsigned int max_priority, const unsigned int aging_threshold) {}

ProcessScheduler::~ProcessScheduler() {
	// TODO
}

void ProcessScheduler::print() const {
	cout << "################################################################################" << endl;

	cout << "Scheduler Configuration: \n"
			<< "* Quantum Threshold: " << quantum_threshold << "\n"
			<< "* Max Priority: " << max_priority << "\n"
			<< "* Aging Threshold: " << aging_threshold << "\n"
			<< endl;

	cout << "State: \n"
			<< "* Quantum Counter: " << quantum_counter << "\n"
			<< "* Next Process ID: " << next_pid << "\n"
			<< endl;

	cout << "Current Process: ";
	if (has_current_process()) {
		cout << "\n----------------------------------------\n";
		current_process->print();
		cout << "----------------------------------------" << endl;
	}
	else {
		cout << "N/A" << endl;
	}

	for (unsigned int i{max_priority + 1}; i > 0; --i) {
		cout << endl;
		cout << "Priority Queue " << i - 1 << ": \n";
		priority_queues[i - 1].print();

	}
	cout << "################################################################################" << endl;
}

bool ProcessScheduler::has_current_process() const {
	return false; // TODO
}

// Swap out Current Process and reset the quantum_counter, if no Current Process or the newly added Process has higher priority.
void ProcessScheduler::add_process(unsigned int execute_time, unsigned int priority) {
	// TODO
}

/*
 * Simulate 1ms at a time.
 * First execute Current Process and tick-up Quantum Counter (if Quantum Threshold is zero, ignore Quantum Counter steps),
 * Delete Current Process and reset Quantum Counter if it has finished execution,
 * Then perform Aging (if Aging Threshold is zero, ignore Aging steps),
 * Swap to next highest priority Process if Current Process has finished execution,
 * Otherwise, swap out Current Process and reset Quantum Counter, if have a higher priority Process or reached/exceeded Quantum Threshold.
 * Repeat for every ms.
 * Do nothing if no Process to execute.
 */
void ProcessScheduler::simulate(unsigned int time) {
	// TODO
}
