#include "helper.h"
#include "circuitgraph.h"
#include "Components/circuitcomponent.h"

#include <QDebug>

#include <set>
#include <cmath>
#include <queue>
#include <vector>

#include <iostream>

#include <Eigen/Core>
#include <Eigen/QR>

CircuitGraph::CircuitGraph() = default;

std::string
CircuitGraph::calculateGraph(const std::map<std::string, CircuitComponent*> &pool)
{
    // 1. Whether there is exactly one battery

    // 2. Whether the battery is short connected

    // 3. Whether there is dangling component

    // 4. Whether it is a complex circuit
    //    (a circuit other than parallel-series circuit)

    // 5. Valid circuit

    int batteryCount = 0;

    for (std::pair<std::string, CircuitComponent*> element : pool) {
        if (element.second->getType() == "Battery") {
            batteryCount ++;
            element.second->setI(0);
        } else {
            element.second->setI(0);
            element.second->setV(0);
        }
    }

    if (batteryCount == 0 /* TODO */) {
        return "There is no battery.";
    }

    if (batteryCount > 1 /* TODO */) {
        return "There are more than one battery.";
    }

    this->reset();
    this->recordComponents(pool);
    this->groupWires();
    std::string buildResult = this->buildGraph();

    if (buildResult != "") {
        return buildResult;
    }

    std::string calResult = recursiveCalculate();

    if (calResult != "") {
        return calResult;
    }

    return "Valid circuit.";
}

void
CircuitGraph::recordComponents(const std::map<std::string, CircuitComponent*> &pool) {
    for (std::pair<std::string, CircuitComponent*> element : pool) {
        components.push_back(element.second);
    }
}

void
CircuitGraph::groupWires() {
    // consider all the poles of the non-wire components
    // want to group poles connected directly or by wire
    groups.init(components.size() * 2);

    // group poles that directly connected
    for (int i = 0; i < components.size(); i++) {
        for (int j = i + 1; j < components.size(); j++) {

            for (int x = 0; x < 2; x++) {
                for (int y = 0; y < 2; y++) {

                    QPoint pX = components[i]->getTerminal(x);
                    QPoint pY = components[j]->getTerminal(y);
                    int idX = i * 2 + x;
                    int idY = j * 2 + y;

                    if (Helper::isOverlapped(pX, pY)) {
                        // Combine two points
                        groups.join(idX, idY);
                    }
                }
            }
        }
    }

    for (int i = 0; i < components.size(); i++) {
        if (components[i]->getType() == "Wire") {
            // Combine two ends of a wire
            groups.join(i * 2, i * 2 + 1);
        }
    }

    // reassign group number to every point
    // so that each group of points which are connected
    // will be assigned with a same ID

    groups.createGroups();
}

std::string
CircuitGraph::buildGraph()
{
    int batteryL = -1;
    int batteryR = -1;

    for (int i = 0; i < components.size(); i++) {
        if (components[i]->getType() == "Battery") {
            batteryL = groups.getGroup(2 * i);
            batteryR = groups.getGroup(2 * i + 1);
        }
    }

    if (batteryL == batteryR) {
        return "Short circuit.";
    }

    // Consider each group as a "node" and the lightbulbs, resistors and motors as edges
    std::vector<std::vector<int> > adj;
    int m = groups.numOfGroups();
    adj.resize(m);
    for (int i = 0; i < components.size(); i++) {
        if (components[i]->getType() != "Battery" && components[i]->getType() != "Wire") {
            int x = groups.getGroup(2 * i);
            int y = groups.getGroup(2 * i + 1);
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    // Find pole groups that are connected to nothing.
    for (int i = 0; i < m; i++) {
        if (i != batteryL && i != batteryR
                && adj[i].size() == 1) {
            return "Dangling component(s).";
        }
    }

    bool closed = false;

    // traverse from pole batteryL
    std::vector<bool> visited(m);
    std::queue<int> q;

    q.push(batteryL);
    visited[batteryL] = true;

    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int x : adj[cur]) {
            if (!visited[x]) {
                q.push(x);
                visited[x] = true;
            }
        }
    }

    // if batteryR is visited, there is a closed circuit
    if (visited[batteryR] /* TODO */) {
        closed = true;
    }

    // TODO: keep the visit record, traverse from pole batteryR


    // if any pole group is not visited

    for (int i{0}; i < adj.size(); ++i) {
        for (int x : adj[i]) {
            if (!visited[x]) {
                return "Dangling component(s).";
            }
        }
    }

    return closed? "" : "Open circuit.";
}

void
CircuitGraph::searchLoop(int curr_v, const std::vector<std::tuple<CircuitComponent*, int, int, int, int>>& edges, std::vector<std::tuple<CircuitComponent*, int, int, int, int>>& trait, std::vector<bool>& visit, int end, std::vector<std::vector<double>>& equations) {
    visit[curr_v] = true;
    if (curr_v == end) {
        std::vector<double> eq(edges.size(), 0);
        for (auto& edge: trait) {
            CircuitComponent* cc;
            int idx, x, y, dir;
            std::tie(cc, idx, x, y, dir) = edge;
            eq[idx] = cc->getR() * dir;
        }
        equations.push_back(eq);
    }
    else {
        for (auto& edge: edges) {
            CircuitComponent* cc;
            int idx, x, y, dir;
            std::tie(cc, idx, x, y, dir) = edge;
            if ((x == curr_v || y == curr_v) && cc->getType() != "Battery") {
                int dir = 1;
                int other;
                if (y == curr_v) {
                    other = x;
                    dir = -1;
                }
                else {
                    other = y;
                    dir = 1;
                }
                if (!visit[other]) {
                    trait.push_back(std::make_tuple(cc, idx, curr_v, other, dir));
                    searchLoop(other, edges, trait, visit, end, equations);
                }
            }
        }
    }
    visit[curr_v] = false;
    if (!trait.empty()) trait.pop_back();
}

std::string
CircuitGraph::recursiveCalculate() {

    int v = groups.numOfGroups();
    int batteryL = -1;
    int batteryR = -1;
    double batteryVoltage = 0;
    std::vector<std::tuple<CircuitComponent*, int, int, int, int>> edges;
    for (int i = 0; i < components.size(); i++) {
        if (components[i]->getType() != "Wire" && components[i]->getType() != "Battery") {
            int x = groups.getGroup(2 * i);
            int y = groups.getGroup(2 * i + 1);
            edges.push_back(std::make_tuple(components[i], static_cast<int>(edges.size()), x, y, 1));
        }
        if (components[i]->getType() == "Battery") {
            batteryL = groups.getGroup(2 * i);
            batteryR = groups.getGroup(2 * i + 1);
            if (batteryL > batteryR) {
                std::swap(batteryL, batteryR);
            }
            batteryVoltage = components[i]->getV();
            edges.push_back(std::make_tuple(components[i], static_cast<int>(edges.size()), batteryL, batteryR, 1));
        }
    }
    int e = edges.size();

    std::vector<std::vector<double>> equations;
    std::vector<double> rhs;
    // KCL
    equations.resize(v);
    rhs.resize(v, 0);
    for (auto& eq: equations) {
        eq.resize(e, 0);
    }
    for (int i=0; i<e; i++) {
        int x, y;
        std::tie(std::ignore, std::ignore, x, y, std::ignore) = edges[i];
        equations[x][i] = -1;
        equations[y][i] = 1;
    }
    // KVL
    std::vector<std::tuple<CircuitComponent*, int, int, int, int>> trait;
    std::vector<bool> visit(v, false);
    searchLoop(batteryL, edges, trait, visit, batteryR, equations);
    rhs.resize(equations.size(), batteryVoltage);
    // solve
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(equations.size(), e);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(equations.size());
    for (int i=0; i<equations.size(); i++) {
        for (int j=0; j<e; j++) {
            A(i, j) = equations[i][j];
        }
        b(i) = rhs[i];
    }
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    for (int i=0; i<e; i++) {
        double _I = x(i);
        std::get<0>(edges[i])->setI(std::abs(_I));
        if (std::get<0>(edges[i])->getType() != "Battery") {
            std::get<0>(edges[i])->setV(std::abs(_I)*std::get<0>(edges[i])->getR());
        }
    }

    return "Valid circuit.";
}

void
CircuitGraph::reset()
{
    components.clear();
}
