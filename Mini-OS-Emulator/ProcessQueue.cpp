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
	for (ProcessNode* current_node{sentinel->next};
			 current_node != sentinel;
			 current_node = current_node->next,
			 delete current_node->prev->process,
			 delete current_node->prev) {}
	delete sentinel;
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

// TODO
// Performs Aging on all Processes in ProcessQueue. Extracts and returns a ProcessQueue of Processes with incremented priority (can be empty).
ProcessQueue* ProcessQueue::perform_aging(unsigned int time, const unsigned int aging_threshold) {
	ProcessQueue* aged_queue = new ProcessQueue;
	ProcessNode* current_node{sentinel->next};
	while (current_node != sentinel) {
		current_node->process->wait(time);
		if (current_node->process->get_aging_counter() >= aging_threshold) {
			current_node->process->promote_priority();
			current_node->process->reset_aging_counter();
			current_node = current_node->next;
			Process* removed_process = remove(current_node->prev);
	 		aged_queue->enqueue(removed_process);
		}
		else {
			current_node = current_node->next;
		}
	}
	return aged_queue;
}

void ProcessQueue::merge_back(ProcessQueue* process_queue) {
	if (process_queue->is_empty()) {
		delete process_queue;
		return;
	}
	ProcessNode* new_tail_node = process_queue->sentinel->prev;
	sentinel->prev->next = process_queue->sentinel->next;
	process_queue->sentinel->next->prev = sentinel->prev;
	new_tail_node->next = sentinel;
	sentinel->prev = new_tail_node;
	delete process_queue->sentinel;
}

void ProcessQueue::enqueue(Process* process) {
	ProcessNode* new_process_node = new ProcessNode{process, sentinel, sentinel->prev};
	sentinel->prev->next = new_process_node;
	sentinel->prev = new_process_node;
}

// Remove Process from the front of ProcessQueue and returns it.
Process* ProcessQueue::dequeue() {
	return remove(sentinel->next);
}

bool ProcessQueue::is_empty() const {
	return sentinel->next == sentinel;
}

// Be very careful when deleting the ProcessNode, don't accidentally delete the Process that we actually want to extract and return.
Process* ProcessQueue::remove(ProcessNode* process_node) {
	if (process_node == sentinel) { return nullptr; }
	process_node->prev->next = process_node->next;
	process_node->next->prev = process_node->prev;
	Process* removed_process = process_node->process;
	delete process_node;
	return removed_process;
}

Process* ProcessQueue::get_head() const {
	return !is_empty() ? sentinel->next->process : nullptr;
}
