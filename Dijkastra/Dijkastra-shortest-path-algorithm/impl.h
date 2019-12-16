#ifndef IMPL_H
#define IMPL_H

#include <string>
#include "graph.h"

class Impl
{
public:
    Impl(Graph *g);

    void deleteComponent(std::string name);

private:
    Graph* graph;
};

#endif // IMPL_H
