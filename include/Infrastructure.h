#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include "MetroGraph.h"

#include <string>
#include <vector>
#include <unordered_map>

struct MSTEdge
{
    std::string source;
    std::string destination;
    double weight;
};

struct MSTResult
{
    bool connected;
    std::vector<MSTEdge> edges;
    double totalCost;
};


class DisjointSet
{
private:
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;

public:
    void makeSet(const std::vector<std::string>& stations);

    std::string find(const std::string& station);

    bool unite(
        const std::string& first,
        const std::string& second
    );
};


class Infrastructure
{
private:
    const MetroGraph& graph;

public:
    Infrastructure(const MetroGraph& graph);

    MSTResult kruskalMST() const;
};

#endif