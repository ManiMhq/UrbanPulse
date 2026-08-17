#ifndef METROCONTROLLER_H
#define METROCONTROLLER_H

#include "MetroGraph.h"
#include "Routing.h"
#include "Infrastructure.h"
#include "ExpressNetwork.h"
#include "BellmanFord.h"
#include "MetroOperations.h"
#include "NetworkAnalysis.h"

#include <string>
#include <vector>


class MetroController
{
private:
    MetroGraph graph;

    Routing routing;
    Infrastructure infrastructure;

    ExpressNetwork expressNetwork;
    BellmanFordNetwork bellmanNetwork;

    FloydWarshall floyd;
    FlowNetwork flowNetwork;

    CriticalNetworkAnalyzer criticalAnalyzer;
    StationSearch stationSearch;


    void showMenu() const;

    void printStations() const;

    void printPath(
        const std::vector<std::string>& path
    ) const;


    void handleReachability();

    void handleDijkstra();

    void handleMST();

    void handleExpressRoute();

    void handleBellmanFord();

    void handleTrainScheduling();

    void handleDispatchQueue();

    void handleAnalytics();

    void handleSimulation();

    void handleFloydWarshall();

    void handleMaxFlow();

    void handleCriticalNetwork();

    void handleStationSearch();


public:
    MetroController();

    void run();
};


#endif