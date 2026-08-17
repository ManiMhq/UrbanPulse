#include "MetroGraph.h"

void MetroGraph::addStation(const std::string& station)
{
    if (adjacencyList.find(station) == adjacencyList.end())
    {
        adjacencyList[station] = {};
    }
}

void MetroGraph::addRoute(const std::string& source,const std::string& destination,double distance,double time)
{
    addStation(source);
    addStation(destination);

    adjacencyList[source].push_back({destination, distance, time});

    adjacencyList[destination].push_back({source, distance, time});
}

bool MetroGraph::hasStation(const std::string& station) const
{
    return adjacencyList.find(station) != adjacencyList.end();
}

const std::vector<Edge>& MetroGraph::getNeighbors(const std::string& station) const
{
    return adjacencyList.at(station);
}

std::vector<std::string> MetroGraph::getStations() const
{
    std::vector<std::string> stations;

    for (const auto& item : adjacencyList)
    {
        stations.push_back(item.first);
    }

    return stations;
}