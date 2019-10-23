/*
 * Complete the ProcessScheduler definitions marked by TODO
 * print() has already been defined for your debugging convenience.
 *
 * You may add your own helper classes, structs, and functions here.
 */

#include "ProcessScheduler.h"

// TODO, You may also use initializer list syntax " : ".
ProcessScheduler::ProcessScheduler(const unsigned int quantum_threshold, const unsigned int max_priority, const unsigned int aging_threshold) {
	this->quantum_threshold = quantum_threshold;
	this->max_priority = max_priority;
	this->aging_threshold = aging_threshold;
	this->priority_queues = new ProcessQueue[max_priority+1];
}

ProcessScheduler::~ProcessScheduler() {
	for (unsigned int i{max_priority + 1}; i > 0; --i)
		delete priority_queues[i-1];
	delete [] priority_queues;
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
	return (current_process != nullptr);
}

// Swap out Current Process and reset the quantum_counter, if no Current Process or the newly added Process has higher priority.
void ProcessScheduler::add_process(unsigned int execute_time, unsigned int priority) {
	if (!has_current_process()) {
		current_process = new Process{next_pid++, execute_time, priority};
	}
	else if (current_process->get_priority() < priority) {
		quantum_counter = 0;
		priority_queues[current_process->get_priority()].enqueue(current_process);
		current_process = new Process{next_pid++, execute_time, priority};
	}
	else {
		priority_queues[priority].enqueue(new Process{next_pid++, execute_time, priority});
	}
}

/*
 * Simulate 1ms at a time.
 * First execute Current Process and tick-up Quantum Counter (if Quantum Threshold is zero, ignore Quantum Counter steps),
 * Delete Current Process and reset Quantum Counter if Current Process has finished execution,
 * Then perform Aging (if Aging Threshold is zero, ignore Aging steps),
 * Swap to next highest priority Process if Current Process has finished execution,
 * Otherwise, swap out Current Process and reset Quantum Counter, if have a higher priority Process or reached/exceeded Quantum Threshold.
 * Repeat for every ms.
 * Do nothing if no Process to execute.
 */
void ProcessScheduler::simulate(unsigned int time) {
	const EXEC_TIME = 1;

	for (unsigned int i = 0; i < time; ++i) {
		if (current_process == nullptr) {
			bool all_empty = true;
			for (unsigned int i{max_priority + 1}; i > 0; --i) {
				if (!priority_queues[i-1].is_empty())
					all_empty = false;
			}
			if (all_empty)
				continue;
		}

		current_process->execute(EXEC_TIME);

		if (quantum_threshold != 0) {
			++quantum_counter;
		}

		if (current_process->get_execute_time() == 0) {
			delete current_process;
			current_process = nullptr;
			quantum_counter = 0;
		}

	  // priority_queues[i-1].perform_aging(EXEC_TIME, aging_threshold);
		if (aging_threshold != 0) {
			bool start_aging = false;
			for (unsigned int i{max_priority + 1}; i > 0; --i) {
				if (start_aging)
					priority_queues[i].merge_back([i-1].perform_aging(EXEC_TIME, aging_threshold));
				else if (!priority_queues[i-1].is_empty() || (current_process != nullptr && current_process->get_priority() == i-1))
					start_aging = true;
			}
		}

		// search the next heighest priority process
		Process* next_process;
		for (unsigned int i{max_priority + 1}; i > 0; --i) {
			if (!priority_queues[i-1].is_empty()) {
				next_process = priority_queues[i-1].dequeue();
				break;
			}
		}

		if (current_process == nullptr) {
			current_process = next_process;
		}
		else if ((quantum_threshold != 0 && quantum_counter >= quantum_threshold) || (next_process->get_priority() > current_process->get_priority())){
			priority_queues[current_process->get_priority()].enqueue(current_process);
			current_process = next_process;
			quantum_counter = 0;
		}
	}
}
