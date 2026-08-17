#include "BellmanFord.h"

#include <unordered_map>
#include <limits>
#include <algorithm>


void BellmanFordNetwork::addDirectedEdge(const std::string& source,const std::string& destination,double weight)
{
    stations.insert(source);
    stations.insert(destination);

    edges.push_back({source,destination,weight});
}


BFResult BellmanFordNetwork::shortestPath(const std::string& source,const std::string& destination) const
{
    if (stations.find(source) == stations.end() || stations.find(destination) == stations.end())
    {
        return {false, false, {}, 0};
    }

    const double INF = std::numeric_limits<double>::infinity();

    std::unordered_map<std::string, double> distance;
    std::unordered_map<std::string, std::string> previous;

    for (const std::string& station : stations)
    {
        distance[station] = INF;
    }

    distance[source] = 0;

    int vertexCount = static_cast<int>(stations.size());

    for (int i = 1; i <= vertexCount - 1; i++)
    {
        bool changed = false;

        for (const BFEdge& edge : edges)
        {
            if (distance[edge.source] == INF)
            {
                continue;
            }

            double newCost = distance[edge.source] + edge.weight;

            if (newCost < distance[edge.destination])
            {
                distance[edge.destination] = newCost;

                previous[edge.destination] = edge.source;

                changed = true;
            }
        }

        if (!changed)
        {
            break;
        }
    }

    for (const BFEdge& edge : edges)
    {
        if (distance[edge.source] == INF)
        {
            continue;
        }

        if (distance[edge.source] + edge.weight < distance[edge.destination])
        {
            return {false,true,{},0};
        }
    }

    if (distance[destination] == INF)
    {
        return {false,false,{},0};
    }

    std::vector<std::string> path;

    std::string current = destination;

    while (current != source)
    {
        path.push_back(current);

        current = previous[current];
    }

    path.push_back(source);

    std::reverse(path.begin(),path.end()
    );

    return {true,false,path,distance[destination]};
}