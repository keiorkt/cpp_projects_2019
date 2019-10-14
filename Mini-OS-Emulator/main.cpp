/*
 * Do NOT modify or submit this file.
 * This file is IGNORED during grading.
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "ProcessScheduler.h"

int main() {
	cout << "Welcome to the Mini Operating System Emulator (TM)!" << endl;
	cout << "Please specify the quantum threshold (ms) of our scheduler: ";
	unsigned int quantum_threshold;
	cin >> quantum_threshold;

	cout << "Please specify the maximum priority (inclusive) allowed for processes in our scheduler: ";
	unsigned int max_priority;
	cin >> max_priority;

	cout << "Please specify the aging threshold (ms) of our scheduler: ";
	unsigned int aging_threshold;
	cin >> aging_threshold;

	ProcessScheduler process_scheduler{quantum_threshold, max_priority, aging_threshold};

	char action;
	unsigned int execute_time, priority, time, time_elapsed = 0;
	while (true) {
		cout << endl;
		cout << "T. Get the time elapsed (ms) since the Process Scheduler was initialized." << endl;
		cout << "P. Print the Process Scheduler." << endl;
		cout << "A. Add a Process to the Process Scheduler." << endl;
		cout << "S. Simulate the Process Scheduler for the given time period (ms)." << endl;
		cout << "Q. Quit the Emulator." << endl;
		cout << "Choose an action: ";
		cin >> action;

		switch (action) {
		case 'T':
		case 't':
			cout << "Time elapsed (ms): " << time_elapsed << endl;
			break;

		case 'P':
		case 'p':
			process_scheduler.print();
			break;

		case 'A':
		case 'a':
			do {
				cout << "Please specify the total execution time (> 0 ms) required for this Process: ";
				cin >> execute_time;
			} while (execute_time <= 0);
			do {
				cout << "Please specify the initial priority level (<= " << max_priority << ") of this Process: ";
				cin >> priority;
			} while (priority > max_priority);
			process_scheduler.add_process(execute_time, priority);
			break;

		case 'S':
		case 's':
			do {
				cout << "Enter the time period (ms) you would like to simulate the Process Scheduler for: ";
				cin >> time;
			} while (time <= 0);
			time_elapsed += time;
			process_scheduler.simulate(time);
			break;

		case 'Q':
		case 'q':
			cout <<"Quitting..." << endl;
			return 0;

		default:
			cout << "Invalid action." << endl;
			break;
		}
	}

	return 0;
}
