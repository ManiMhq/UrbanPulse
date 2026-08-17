#ifndef ROUTING_H
#define ROUTING_H

#include "MetroGraph.h"

#include <string>
#include <vector>

struct PathResult
{
    bool found;
    std::vector<std::string> path;
    double cost;
};

class Routing
{
private:
    const MetroGraph& graph;

public:
    Routing(const MetroGraph& graph);

    PathResult bfs(const std::string& source,const std::string& destination) const;

    PathResult dijkstra(const std::string& source,const std::string& destination,const std::string& criterion) const;
};

#endif