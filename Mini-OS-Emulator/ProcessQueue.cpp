/*
 * Complete the ProcessQueue definitions marked by TODO
 * Default Constructor has already been defined, as failing to initialize sentinel to point to itself is a common yet frustrating pitfall.
 * print() has already been defined for your debugging convenience.
 *
 * You may add your own helper classes, structs, and functions here.
 */

#include "ProcessQueue.h"

/*
 * These will fail as sentinel doesn't exist yet to point to itself.
 * Initializer List : sentinel{new ProcessNode{nullptr, sentinel, sentinel}}
 * sentinel = new ProcessNode{nullptr, sentinel, sentinel};
 */
ProcessQueue::ProcessQueue() {
	sentinel = new ProcessNode{};
	sentinel->prev = sentinel->next = sentinel; // Need to do this on a separate line, otherwise sentinel doesn't exist yet to point to itself.
}

ProcessQueue::~ProcessQueue() {
	// TODO
}

void ProcessQueue::print() const {
	cout << "================================================================================" << endl;
	if (is_empty()) {
		cout << "This ProcessQueue is empty." << endl;
	}
	else {
		for (ProcessNode* current_node{sentinel->next}; current_node != sentinel->prev; current_node = current_node->next) {
			current_node->process->print();
			cout << "--------------------------------------------------------------------------------" << endl;
		}
		sentinel->prev->process->print();
	}
	cout << "================================================================================" << endl;
}

ProcessQueue* ProcessQueue::perform_aging(unsigned int time, const unsigned int aging_threshold) {
	return nullptr; // TODO
}

void ProcessQueue::merge_back(ProcessQueue* process_queue) {
	// TODO
}

void ProcessQueue::enqueue(Process* process) {
	// TODO
}

Process* ProcessQueue::dequeue() {
	return nullptr; // TODO
}

bool ProcessQueue::is_empty() const {
	return false; // TODO
}

// Be very careful when deleting the ProcessNode, don't accidentally delete the Process that we actually want to extract and return.
Process* ProcessQueue::remove(ProcessNode* process_node) {
	return nullptr; // TODO
}
