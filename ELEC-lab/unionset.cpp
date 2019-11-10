#include "unionset.h"

UnionSet::UnionSet() = default;

void
UnionSet::init(int n)
{
    this->n = n;
    counter = 0;

    father.resize(n);
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }

    groupMapping.resize(n);
    for (int i = 0; i < n; i++) {
        groupMapping[i] = -1;
    }
}

void
UnionSet::createGroups()
{
    for (int i = 0; i < n; i++) {
        if (groupMapping[find(i)] == -1) {
            groupMapping[find(i)] = counter++;
        }
    }
}

int
UnionSet::getGroup(int x)
{
    return groupMapping[find(x)];
}

int
UnionSet::numOfGroups()
{
    return counter;
}

void
UnionSet::join(int x, int y)
{
    if (find(x) != find(y)) {
        father[find(x)] = find(y);
    }
}

int
UnionSet::find(int x)
{
    if (father[x] == x) {
        return x;
    } else {
        return father[x] = find(father[x]);
    }
}
