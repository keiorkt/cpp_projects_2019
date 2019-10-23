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
	for (ProcessNode* current_node{sentinel->next}; current_node != sentinel; current_node = current_node->next, delete current_node->prev) {}
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
ProcessQueue* ProcessQueue::perform_aging(unsigned int time, const unsigned int aging_threshold) {
	ProcessQueue* process_queue = new ProcessQueue{};
	for (ProcessNode* current_node{sentinel->next}; current_node != sentinel; current_node = current_node->next) {
		current_node->process->wait(time);
		if (current_node->process->get_aging_counter() >= aging_threshold) {
			current_node->process->promote_priority();
	 		process_queue->enqueue(remove(current_node));
		}
	}
	return process_queue;
}

void ProcessQueue::merge_back(ProcessQueue* process_queue) {
	if (process_queue->is_empty()) return;
	ProcessNode* new_tail_node = process_queue->sentinel->prev;
	this->sentinel->prev->next = process_queue->sentinel->next;
	process_queue->sentinel->next->prev = this->sentinel->prev;
	new_tail_node->next = this->sentinel;
	this->sentinel->prev = new_tail_node;
	delete process_queue->sentinel;
}

void ProcessQueue::enqueue(Process* process) {
	ProcessNode* new_process_node = new ProcessNode{process, sentinel->next, sentinel};
	sentinel->next->prev = new_process_node;
	sentinel->next = new_process_node;
}

Process* ProcessQueue::dequeue() {
	return remove(sentinel);
}

bool ProcessQueue::is_empty() const {
	return (sentinel->next == sentinel);
}

// Be very careful when deleting the ProcessNode, don't accidentally delete the Process that we actually want to extract and return.
Process* ProcessQueue::remove(ProcessNode* process_node) {
	if (!is_empty()) {
		for (ProcessNode* current_node{sentinel->next}; current_node != sentinel; current_node = current_node->next) {
			if (current_node == process_node) {
				current_node->next->prev = current_node->prev;
				current_node->prev->next = current_node->next;
				Process* process = current_node->process;
				delete current_node;
				return process;
			}
		}
	}
	return nullptr;
}
