#include "NetworkAnalysis.h"

#include <limits>
#include <algorithm>
#include <queue>

FloydWarshall::FloydWarshall(const MetroGraph& graph)
{
    stations = graph.getStations();

    int n =
        static_cast<int>(stations.size());

    for (int i = 0; i < n; i++)
    {
        index[stations[i]] = i;
    }

    const double INF =
        std::numeric_limits<double>::infinity();


    distanceMatrix.assign(
        n,
        std::vector<double>(n, INF)
    );

    timeMatrix.assign(
        n,
        std::vector<double>(n, INF)
    );

    nextDistance.assign(
        n,
        std::vector<int>(n, -1)
    );

    nextTime.assign(
        n,
        std::vector<int>(n, -1)
    );


    for (int i = 0; i < n; i++)
    {
        distanceMatrix[i][i] = 0;
        timeMatrix[i][i] = 0;
        nextDistance[i][i] = i;
        nextTime[i][i] = i;
    }


    for (const std::string& source : stations)
    {
        int u = index[source];

        for (const Edge& edge :graph.getNeighbors(source))
        {
            int v =index[edge.destination];


            if (edge.distance <distanceMatrix[u][v])
            {
                distanceMatrix[u][v] =edge.distance;
                nextDistance[u][v] = v;
            }


            if (edge.time <timeMatrix[u][v])
            {
                timeMatrix[u][v] =edge.time;
                nextTime[u][v] = v;
            }
        }
    }


    runFloyd(distanceMatrix,nextDistance
    );

    runFloyd(timeMatrix,nextTime
    );
}

void FloydWarshall::runFloyd(std::vector<std::vector<double>>& matrix,std::vector<std::vector<int>>& next)
{
    int n =static_cast<int>(matrix.size());

    const double INF =std::numeric_limits<double>::infinity();


    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][k] == INF ||matrix[k][j] == INF)
                {
                    continue;
                }

                double newCost =matrix[i][k] +matrix[k][j];

                if (newCost <matrix[i][j])
                {
                    matrix[i][j] =newCost;

                    next[i][j] =next[i][k];
                }
            }
        }
    }
}

FWPathResult FloydWarshall::shortestPath(const std::string& source,const std::string& destination,const std::string& criterion) const
{
    if (index.find(source) == index.end() ||index.find(destination) == index.end())
    {
        return {false, {}, 0};
    }


    if (criterion != "distance" &&criterion != "time")
    {
        return {false, {}, 0};
    }


    const std::vector<std::vector<double>>& matrix =(criterion == "distance")? distanceMatrix: timeMatrix;

    const std::vector<std::vector<int>>& next =(criterion == "distance")? nextDistance: nextTime;


    int sourceIndex =index.at(source);

    int destinationIndex =index.at(destination);


    if (next[sourceIndex][destinationIndex] == -1)
    {
        return {false, {}, 0};
    }


    std::vector<std::string> path;

    int current =sourceIndex;

    path.push_back(stations[current]);


    while (current != destinationIndex)
    {
        current =next[current][destinationIndex];

        path.push_back(stations[current]);
    }


    return {true,path,matrix[sourceIndex][destinationIndex]};
}

void FlowNetwork::addDirectedRoute(const std::string& source,const std::string& destination,int routeCapacity)
{
    if (routeCapacity < 0)
    {
        return;
    }

    capacity[source][destination] +=routeCapacity;

    capacity[destination][source] += 0;

    neighbors[source].insert(destination);
    neighbors[destination].insert(source);
}


int FlowNetwork::edmondsKarp(const std::string& source,const std::string& destination) const
{
    if (neighbors.find(source) ==neighbors.end() ||neighbors.find(destination) ==neighbors.end())
    {
        return 0;
    }

    auto residual = capacity;

    int maxFlow = 0;

    while (true)
    {
        std::queue<std::string> q;

        std::unordered_map<std::string,std::string> parent;

        std::unordered_set<std::string> visited;

        q.push(source);
        visited.insert(source);

        bool pathFound = false;

        while (!q.empty() && !pathFound)
        {
            std::string current =q.front();
            q.pop();

            for (const std::string& next :neighbors.at(current))
            {
                int residualCapacity = 0;

                auto currentIt =residual.find(current);

                if (currentIt != residual.end())
                {
                    auto nextIt =currentIt->second.find(next);

                    if (nextIt !=currentIt->second.end())
                    {
                        residualCapacity =nextIt->second;
                    }
                }

                if (visited.find(next) ==visited.end() &&residualCapacity > 0)
                {
                    visited.insert(next);

                    parent[next] = current;

                    q.push(next);

                    if (next == destination)
                    {
                        pathFound = true;
                        break;
                    }
                }
            }
        }

        if (!pathFound)
        {
            break;
        }

        int pathFlow =std::numeric_limits<int>::max();

        std::string current =destination;

        while (current != source)
        {
            std::string previous =parent[current];

            pathFlow =
                std::min(pathFlow,residual[previous][current]);

            current = previous;
        }

        current = destination;

        while (current != source)
        {
            std::string previous =parent[current];

            residual[previous][current] -=pathFlow;

            residual[current][previous] +=pathFlow;

            current = previous;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
CriticalNetworkAnalyzer::CriticalNetworkAnalyzer(const MetroGraph& graph): graph(graph){}


void CriticalNetworkAnalyzer::dfs(const std::string& current,const std::string& parent,int& timer,std::unordered_map<std::string, bool>& visited,std::unordered_map<std::string, int>& discovery,
    std::unordered_map<std::string, int>& low,std::unordered_set<std::string>& articulationSet,std::vector<Bridge>& bridges) const
{
    visited[current] = true;

    discovery[current] = timer;
    low[current] = timer;

    timer++;

    int childCount = 0;

    for (const Edge& edge :graph.getNeighbors(current))
    {
        std::string neighbor =edge.destination;

        if (neighbor == parent)
        {
            continue;
        }


        if (!visited[neighbor])
        {
            childCount++;

            dfs(
                neighbor,
                current,
                timer,
                visited,
                discovery,
                low,
                articulationSet,
                bridges
            );

            low[current] =
                std::min(low[current],low[neighbor]);


            if (parent != "" &&low[neighbor] >= discovery[current])
            {
                articulationSet.insert(current);
            }


            if (low[neighbor] > discovery[current])
            {
                bridges.push_back({current,neighbor});
            }
        }
        else
        {
            low[current] =
                std::min(low[current],discovery[neighbor]);
        }
    }


    if (parent == "" &&childCount > 1)
    {
        articulationSet.insert(current);
    }
}


CriticalNetworkResult
CriticalNetworkAnalyzer::analyze() const
{
    std::vector<std::string> stations =graph.getStations();

    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, int> discovery;
    std::unordered_map<std::string, int> low;

    std::unordered_set<std::string>articulationSet;

    std::vector<Bridge> bridges;

    int timer = 0;


    for (const std::string& station : stations)
    {
        visited[station] = false;
    }


    for (const std::string& station : stations)
    {
        if (!visited[station])
        {
            dfs(
                station,
                "",
                timer,
                visited,
                discovery,
                low,
                articulationSet,
                bridges
            );
        }
    }


    std::vector<std::string> articulationPoints(articulationSet.begin(),articulationSet.end());
    std::sort(articulationPoints.begin(),articulationPoints.end());
    return {articulationPoints,bridges};
}

StationSearch::StationSearch(const MetroGraph& graph): graph(graph){}


int StationSearch::levenshteinDistance(const std::string& first,const std::string& second) const
{
    int n =static_cast<int>(first.size());

    int m =static_cast<int>(second.size());


    std::vector<std::vector<int>> dp(n + 1,std::vector<int>(m + 1));


    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }

    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }


    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (first[i - 1] ==second[j - 1])
            {
                dp[i][j] =
                    dp[i - 1][j - 1];
            }
            else
            {
                int deletion =
                    dp[i - 1][j] + 1;

                int insertion =
                    dp[i][j - 1] + 1;

                int replacement =
                    dp[i - 1][j - 1] + 1;

                dp[i][j] =std::min(deletion,std::min(insertion,replacement));
            }
        }
    }

    return dp[n][m];
}


StationSearchResult
StationSearch::findClosestStation(const std::string& input) const
{
    std::vector<std::string> stations =graph.getStations();

    if (stations.empty())
    {
        return {false,"",0};
    }


    std::string bestStation;

    int bestDistance =std::numeric_limits<int>::max();


    for (const std::string& station : stations)
    {
        int currentDistance =
            levenshteinDistance(input,station);

        if (currentDistance <bestDistance)
        {
            bestDistance =currentDistance;

            bestStation =station;
        }
    }


    return {true,bestStation,bestDistance};
}