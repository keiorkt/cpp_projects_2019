#ifndef UNIONSET_H
#define UNIONSET_H

#include <vector>

class UnionSet
{
public:
    UnionSet();

    void init(int n);

    void join(int x, int y);

    void createGroups();

    int getGroup(int x);

    int numOfGroups();

private:
    int n;

    int counter;

    std::vector<int> father;

    std::vector<int> groupMapping;

    int find(int x);
};

#endif // UNIONSET_H
