#ifndef NETWORKANALYSIS_H
#define NETWORKANALYSIS_H

#include "MetroGraph.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


struct FWPathResult
{
    bool found;
    std::vector<std::string> path;
    double cost;
};


class FloydWarshall
{
private:
    std::vector<std::string> stations;

    std::unordered_map<std::string, int> index;

    std::vector<std::vector<double>> distanceMatrix;
    std::vector<std::vector<double>> timeMatrix;

    std::vector<std::vector<int>> nextDistance;
    std::vector<std::vector<int>> nextTime;

    void runFloyd(std::vector<std::vector<double>>& matrix,std::vector<std::vector<int>>& next);

public:
    FloydWarshall(const MetroGraph& graph);

    FWPathResult shortestPath(const std::string& source,const std::string& destination,const std::string& criterion) const;
};

class FlowNetwork
{
private:
    std::unordered_map<std::string,std::unordered_map<std::string, int>> capacity;

    std::unordered_map<std::string,std::unordered_set<std::string>> neighbors;

public:
    void addDirectedRoute(const std::string& source,const std::string& destination,int routeCapacity);

    int edmondsKarp(const std::string& source,const std::string& destination) const;
};

struct Bridge
{
    std::string first;
    std::string second;
};


struct CriticalNetworkResult
{
    std::vector<std::string> articulationPoints;
    std::vector<Bridge> bridges;
};


class CriticalNetworkAnalyzer
{
private:
    const MetroGraph& graph;

    void dfs(const std::string& current,const std::string& parent,int& timer,std::unordered_map<std::string, bool>& visited,std::unordered_map<std::string, 
        int>& discovery,std::unordered_map<std::string, int>& low,std::unordered_set<std::string>& articulationSet,std::vector<Bridge>& bridges) const;

public:
    CriticalNetworkAnalyzer(const MetroGraph& graph);

    CriticalNetworkResult analyze() const;
};

struct StationSearchResult
{
    bool found;
    std::string stationName;
    int distance;
};


class StationSearch
{
private:
    const MetroGraph& graph;

    int levenshteinDistance(const std::string& first,const std::string& second) const;

public:
    StationSearch(const MetroGraph& graph);

    StationSearchResult findClosestStation(const std::string& input) const;
};

#endif