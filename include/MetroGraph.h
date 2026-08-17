#ifndef METROGRAPH_H
#define METROGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

struct Edge
{
    std::string destination;
    double distance;
    double time;
};

class MetroGraph
{
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;

public:
    void addStation(const std::string& station);

    void addRoute(const std::string& source,const std::string& destination,double distance,double time);

    bool hasStation(const std::string& station) const;

    const std::vector<Edge>& getNeighbors(const std::string& station) const;

    std::vector<std::string> getStations() const;
};

#endif