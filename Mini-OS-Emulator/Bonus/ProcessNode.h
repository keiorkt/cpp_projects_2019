/*
 * DO NOT MODIFY!
 */

#ifndef PROCESSNODE_H_
#define PROCESSNODE_H_

#include "Process.h"

class ProcessNode {
	friend class ProcessQueue; // Allows ProcessQueue to access private members of ProcessNode.

public:
	ProcessNode();
	ProcessNode(Process* process, ProcessNode* next, ProcessNode* prev);
	~ProcessNode();

private:
	Process* process{nullptr};
	ProcessNode* next{nullptr};
	ProcessNode* prev{nullptr};
};

#endif /* PROCESSNODE_H_ */
