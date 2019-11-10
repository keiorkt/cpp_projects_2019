#ifndef CIRCUITGRAPH_H
#define CIRCUITGRAPH_H

#include "unionset.h"

#include <map>
#include <string>

class CircuitComponent;

class CircuitGraph
{
public:
    CircuitGraph(); 

    std::string calculateGraph(const std::map<std::string, CircuitComponent*> &pool);

private:

    void reset();

    void recordComponents(const std::map<std::string, CircuitComponent*> &pool);
    void groupWires();
    std::string buildGraph();

    std::string recursiveCalculate();
    void searchLoop(int curr_v, const std::vector<std::tuple<CircuitComponent*, int, int, int, int>>& edges, std::vector<std::tuple<CircuitComponent*, int, int, int, int>>& trait, std::vector<bool>& visit, int end, std::vector<std::vector<double>>& equations);

    std::vector<CircuitComponent*> components;
    UnionSet groups;
};

#endif // CIRCUITGRAPH_H
