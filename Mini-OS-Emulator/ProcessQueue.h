/*
 * You may add your own helper classes, structs, and functions here.
 * However, do NOT modify the existing ProcessQueue class declaration.
 */

#ifndef PROCESSQUEUE_H_
#define PROCESSQUEUE_H_

#include <iostream>
using std::cout;
using std::endl;

#include "ProcessNode.h"

class ProcessQueue {
public:
	ProcessQueue();
	~ProcessQueue();

	void print() const; // Prints all the processes in ProcessQueue.
	// Performs Aging on all Processes in ProcessQueue. Extracts and returns a ProcessQueue of Processes with incremented priority (can be empty).
	ProcessQueue* perform_aging(unsigned int time, const unsigned int aging_threshold);
	void merge_back(ProcessQueue* process_queue); // Merges process_queue to the back of ProcessQueue.

	void enqueue(Process* process); // Insert Process at the back of ProcessQueue.
	Process* dequeue(); // Remove Process from the front of ProcessQueue and returns it.
	bool is_empty() const; // Checks if ProcessQueue is empty, i.e. has no valid elements and only has the sentinel.
	Process* get_head() const;

private:
	Process* remove(ProcessNode* process_node); // Removes the specified ProcessNode and returns its Process. Helper function for perform_aging().
	ProcessNode* sentinel{nullptr}; // sentinel->next and sentinel->prev should point to the front and back node respectively if ProcessQueue is non-empty.
};

#endif /* PROCESSQUEUE_H_ */
