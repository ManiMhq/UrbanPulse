#include "Routing.h"

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <functional>

Routing::Routing(const MetroGraph& graph)
    : graph(graph)
{
}

PathResult Routing::bfs(const std::string& source,const std::string& destination) const
{
    if (!graph.hasStation(source) || !graph.hasStation(destination))
    {
        return {false, {}, 0};
    }

    std::queue<std::string> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> previous;

    q.push(source);
    visited.insert(source);

    while (!q.empty())
    {
        std::string current = q.front();
        q.pop();

        if (current == destination)
        {
            break;
        }

        for (const Edge& edge : graph.getNeighbors(current))
        {
            if (visited.find(edge.destination) == visited.end())
            {
                visited.insert(edge.destination);
                previous[edge.destination] = current;
                q.push(edge.destination);
            }
        }
    }

    if (visited.find(destination) == visited.end())
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

    return {true, path, 0};
}


PathResult Routing::dijkstra(const std::string& source,const std::string& destination,const std::string& criterion) const
{
    if (!graph.hasStation(source) || !graph.hasStation(destination))
    {
        return {false, {}, 0};
    }

    if (criterion != "distance" && criterion != "time")
    {
        return {false, {}, 0};
    }

    const double INF =std::numeric_limits<double>::infinity();

    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;

    for (const std::string& station : graph.getStations())
    {
        distances[station] = INF;
    }

    distances[source] = 0;

    using QueueItem = std::pair<double, std::string>;

    std::priority_queue<QueueItem,std::vector<QueueItem>,std::greater<QueueItem>> pq;

    pq.push({0, source});

    while (!pq.empty())
    {
        double currentCost = pq.top().first;
        std::string current = pq.top().second;

        pq.pop();

        if (currentCost > distances[current])
        {
            continue;
        }

        if (current == destination)
        {
            break;
        }

        for (const Edge& edge : graph.getNeighbors(current))
        {
            double weight;

            if (criterion == "distance")
            {
                weight = edge.distance;
            }
            else
            {
                weight = edge.time;
            }

            double newCost = currentCost + weight;

            if (newCost < distances[edge.destination])
            {
                distances[edge.destination] = newCost;
                previous[edge.destination] = current;

                pq.push({newCost , edge.destination});
            }
        }
    }

    if (distances[destination] == INF)
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

    return {true,path,distances[destination]};
}