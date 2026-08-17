#include "Infrastructure.h"

#include <algorithm>


void DisjointSet::makeSet(const std::vector<std::string>& stations)
{
    parent.clear();
    rank.clear();

    for (const std::string& station : stations)
    {
        parent[station] = station;
        rank[station] = 0;
    }
}


std::string DisjointSet::find(const std::string& station)
{
    if (parent[station] != station)
    {
        parent[station] = find(parent[station]);
    }

    return parent[station];
}


bool DisjointSet::unite(const std::string& first , const std::string& second)
{
    std::string rootFirst = find(first);
    std::string rootSecond = find(second);

    if (rootFirst == rootSecond)
    {
        return false;
    }

    if (rank[rootFirst] < rank[rootSecond])
    {
        parent[rootFirst] = rootSecond;
    }
    else if (rank[rootFirst] > rank[rootSecond])
    {
        parent[rootSecond] = rootFirst;
    }
    else
    {
        parent[rootSecond] = rootFirst;
        rank[rootFirst]++;
    }

    return true;
}


Infrastructure::Infrastructure(const MetroGraph& graph): graph(graph){}


MSTResult Infrastructure::kruskalMST() const
{
    std::vector<MSTEdge> allEdges;

    std::vector<std::string> stations = graph.getStations();

    for (const std::string& source : stations)
    {
        for (const Edge& edge : graph.getNeighbors(source))
        {
            if (source < edge.destination)
            {
                allEdges.push_back({source , edge.destination , edge.distance});
            }
        }
    }

    std::sort(allEdges.begin() , allEdges.end() , [](const MSTEdge& first , const MSTEdge& second)
        {
            if (first.weight != second.weight)
            {
                return first.weight < second.weight;
            }

            if (first.source != second.source)
            {
                return first.source < second.source;
            }

            return first.destination < second.destination;
        }
    );

    DisjointSet disjointSet;

    disjointSet.makeSet(stations);

    std::vector<MSTEdge> mstEdges;

    double totalCost = 0;

    for (const MSTEdge& edge : allEdges)
    {
        if (disjointSet.unite(edge.source , edge.destination))
        {
            mstEdges.push_back(edge);

            totalCost += edge.weight;

            if (mstEdges.size() ==
                stations.size() - 1)
            {
                break;
            }
        }
    }

    bool connected = mstEdges.size() == stations.size() - 1;

    return {connected , mstEdges , totalCost};
}