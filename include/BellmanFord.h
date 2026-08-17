#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <string>
#include <vector>
#include <unordered_set>

struct BFEdge
{
    std::string source;
    std::string destination;
    double weight;
};

struct BFResult
{
    bool found;
    bool negativeCycle;
    std::vector<std::string> path;
    double cost;
};

class BellmanFordNetwork
{
private:
    std::unordered_set<std::string> stations;
    std::vector<BFEdge> edges;

public:
    void addDirectedEdge(
        const std::string& source,
        const std::string& destination,
        double weight
    );

    BFResult shortestPath(
        const std::string& source,
        const std::string& destination
    ) const;
};

#endif