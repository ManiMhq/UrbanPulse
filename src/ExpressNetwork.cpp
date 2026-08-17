#include "ExpressNetwork.h"

#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>


void ExpressNetwork::addStation(const std::string& station)
{
    if (adjacencyList.find(station) == adjacencyList.end())
    {
        adjacencyList[station] = {};
    }
}


void ExpressNetwork::addDirectedRoute(const std::string& source,const std::string& destination,double weight)
{
    addStation(source);
    addStation(destination);

    adjacencyList[source].push_back({destination, weight});
}


std::vector<std::string>
ExpressNetwork::topologicalSort() const
{
    std::unordered_map<std::string, int> inDegree;

    for (const auto& item : adjacencyList)
    {
        inDegree[item.first] = 0;
    }

    for (const auto& item : adjacencyList)
    {
        for (const ExpressEdge& edge : item.second)
        {
            inDegree[edge.destination]++;
        }
    }

    std::queue<std::string> q;

    for (const auto& item : inDegree)
    {
        if (item.second == 0)
        {
            q.push(item.first);
        }
    }

    std::vector<std::string> order;

    while (!q.empty())
    {
        std::string current = q.front();
        q.pop();

        order.push_back(current);

        for (const ExpressEdge& edge :adjacencyList.at(current))
        {
            inDegree[edge.destination]--;

            if (inDegree[edge.destination] == 0)
            {
                q.push(edge.destination);
            }
        }
    }

    if (order.size() != adjacencyList.size())
    {
        return {};
    }

    return order;
}


ExpressPathResult ExpressNetwork::shortestPathDAG(const std::string& source,const std::string& destination) const
{
    if (adjacencyList.find(source) ==adjacencyList.end() ||adjacencyList.find(destination) ==adjacencyList.end())
    {
        return {false, {}, 0};
    }

    std::vector<std::string> order = topologicalSort();

    if (order.empty())
    {
        return {false, {}, 0};
    }

    const double INF = std::numeric_limits<double>::infinity();

    std::unordered_map<std::string, double> distance;
    std::unordered_map<std::string, std::string> previous;

    for (const auto& item : adjacencyList)
    {
        distance[item.first] = INF;
    }

    distance[source] = 0;

    for (const std::string& current : order)
    {
        if (distance[current] == INF)
        {
            continue;
        }

        for (const ExpressEdge& edge : adjacencyList.at(current))
        {
            double newCost = distance[current] + edge.weight;

            if (newCost < distance[edge.destination])
            {
                distance[edge.destination] = newCost;
                previous[edge.destination] = current;
            }
        }
    }

    if (distance[destination] == INF)
    {
        return {false, {}, 0};
    }

    std::vector<std::string> path;

    std::string current = destination;

    while (current != source)
    {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(source);

    std::reverse(path.begin(), path.end());

    return {true , path , distance[destination]
    };
}