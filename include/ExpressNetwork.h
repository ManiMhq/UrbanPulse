#ifndef EXPRESSNETWORK_H
#define EXPRESSNETWORK_H

#include <string>
#include <vector>
#include <unordered_map>

struct ExpressEdge
{
    std::string destination;
    double weight;
};

struct ExpressPathResult
{
    bool found;
    std::vector<std::string> path;
    double cost;
};

class ExpressNetwork
{
private:
    std::unordered_map<std::string,std::vector<ExpressEdge>> adjacencyList;

public:
    void addStation(const std::string& station);

    void addDirectedRoute(const std::string& source,const std::string& destination,double weight);

    ExpressPathResult shortestPathDAG(const std::string& source,const std::string& destination) const;

private:
    std::vector<std::string> topologicalSort() const;
};

#endif