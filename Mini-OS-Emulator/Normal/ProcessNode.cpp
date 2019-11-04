/*
 * Complete the ProcessNode definitions marked by TODO
 * You may add your own helper classes, structs, and functions here.
 */

#include "ProcessNode.h"

// TODO, You may also use initializer list syntax " : ".
ProcessNode::ProcessNode() {}

// TODO, You may also use initializer list syntax " : ".
ProcessNode::ProcessNode(Process* process, ProcessNode* next, ProcessNode* prev) : process{process}, next{next}, prev{prev} {}

// debug
ProcessNode::~ProcessNode() {}
