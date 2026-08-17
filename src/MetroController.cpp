#include "MetroController.h"
#include "Data.h"

#include <iostream>
#include <limits>


MetroController::MetroController(): graph(createQomMetroGraph()),routing(graph),infrastructure(graph),expressNetwork(createExpressNetwork()),bellmanNetwork(createBellmanFordNetwork()),floyd(graph),flowNetwork(createFlowNetwork()),
      criticalAnalyzer(graph),stationSearch(graph){}


void MetroController::showMenu() const
{
    std::cout
        << "\n========================================\n"
        << "          QOM METRO SYSTEM\n"
        << "========================================\n"
        << "1.  Show stations\n"
        << "2.  Check station reachability (BFS)\n"
        << "3.  Find shortest route (Dijkstra)\n"
        << "4.  Minimum spanning network (Kruskal)\n"
        << "5.  Express line shortest path (DAG)\n"
        << "6.  Bellman-Ford analysis\n"
        << "7.  Train interval scheduling\n"
        << "8.  Train dispatch priority queue\n"
        << "9.  Operational data analysis\n"
        << "10. Passenger simulation\n"
        << "11. All-pairs shortest path (Floyd-Warshall)\n"
        << "12. Maximum passenger flow\n"
        << "13. Critical stations and bridges\n"
        << "14. Station typo search\n"
        << "0.  Exit\n"
        << "========================================\n"
        << "Choice: ";
}


void MetroController::printStations() const
{
    std::cout
        << "\nAvailable stations:\n";

    std::vector<std::string> stations =
        graph.getStations();

    for (const std::string& station : stations)
    {
        std::cout
            << "- "
            << station
            << '\n';
    }

    std::cout << '\n';
}


void MetroController::printPath(
    const std::vector<std::string>& path
) const
{
    for (int i = 0;
         i < static_cast<int>(path.size());
         i++)
    {
        std::cout << path[i];

        if (i !=
            static_cast<int>(path.size()) - 1)
        {
            std::cout << " -> ";
        }
    }

    std::cout << '\n';
}


void MetroController::handleReachability()
{
    printStations();

    std::string source;
    std::string destination;

    std::cout
        << "Source station: ";

    std::getline(
        std::cin,
        source
    );

    std::cout
        << "Destination station: ";

    std::getline(
        std::cin,
        destination
    );


    PathResult result =
        routing.bfs(
            source,
            destination
        );


    if (result.found)
    {
        std::cout
            << "\nPath exists:\n";

        printPath(result.path);
    }
    else
    {
        std::cout
            << "\nNo path found.\n";
    }
}


void MetroController::handleDijkstra()
{
    printStations();

    std::string source;
    std::string destination;
    std::string criterion;


    std::cout
        << "Source station: ";

    std::getline(
        std::cin,
        source
    );


    std::cout
        << "Destination station: ";

    std::getline(
        std::cin,
        destination
    );


    std::cout
        << "Criterion (distance/time): ";

    std::getline(
        std::cin,
        criterion
    );


    PathResult result =
        routing.dijkstra(
            source,
            destination,
            criterion
        );


    if (!result.found)
    {
        std::cout
            << "\nInvalid input or no path found.\n";

        return;
    }


    std::cout
        << "\nShortest path:\n";

    printPath(result.path);


    std::cout
        << "Total cost: "
        << result.cost;


    if (criterion == "distance")
    {
        std::cout << " km\n";
    }
    else
    {
        std::cout << " minutes\n";
    }
}


void MetroController::handleMST()
{
    MSTResult result =
        infrastructure.kruskalMST();


    if (!result.connected)
    {
        std::cout
            << "\nGraph is not connected.\n";

        return;
    }


    std::cout
        << "\nMST edges:\n";


    for (const MSTEdge& edge :
         result.edges)
    {
        std::cout
            << edge.source
            << " <-> "
            << edge.destination
            << " | Cost: "
            << edge.weight
            << '\n';
    }


    std::cout
        << "\nTotal MST cost: "
        << result.totalCost
        << " km\n";

    std::cout
        << "Number of edges: "
        << result.edges.size()
        << '\n';
}


void MetroController::handleExpressRoute()
{
    std::string source;
    std::string destination;


    std::cout
        << "Source: ";

    std::getline(
        std::cin,
        source
    );


    std::cout
        << "Destination: ";

    std::getline(
        std::cin,
        destination
    );


    ExpressPathResult result =
        expressNetwork.shortestPathDAG(
            source,
            destination
        );


    if (!result.found)
    {
        std::cout
            << "\nNo valid express path found.\n";

        return;
    }


    std::cout
        << "\nShortest express path:\n";

    printPath(result.path);


    std::cout
        << "Total cost: "
        << result.cost
        << '\n';
}


void MetroController::handleBellmanFord()
{
    std::string source;
    std::string destination;


    std::cout
        << "Source: ";

    std::getline(
        std::cin,
        source
    );


    std::cout
        << "Destination: ";

    std::getline(
        std::cin,
        destination
    );


    BFResult result =
        bellmanNetwork.shortestPath(
            source,
            destination
        );


    if (result.negativeCycle)
    {
        std::cout
            << "\nNegative cycle detected.\n";

        return;
    }


    if (!result.found)
    {
        std::cout
            << "\nNo path found.\n";

        return;
    }


    std::cout
        << "\nShortest path:\n";

    printPath(result.path);


    std::cout
        << "Total cost: "
        << result.cost
        << '\n';
}


void MetroController::handleTrainScheduling()
{
    TrainScheduler scheduler;

    std::vector<TrainInterval> trains =
        createTrainIntervals();


    std::vector<TrainInterval> selected =
        scheduler.selectMaximumTrains(
            trains
        );


    std::cout
        << "\nSelected trains:\n";


    for (const TrainInterval& train :
         selected)
    {
        std::cout
            << train.trainName
            << " | "
            << train.arrivalTime
            << " -> "
            << train.departureTime
            << '\n';
    }


    std::cout
        << "Maximum number of trains: "
        << selected.size()
        << '\n';
}


void MetroController::handleDispatchQueue()
{
    TrainDispatchQueue dispatchQueue;

    std::vector<DispatchTrain> trains =
        createDispatchTrains();


    for (const DispatchTrain& train :
         trains)
    {
        dispatchQueue.addTrain(
            train.trainName,
            train.priority,
            train.delay
        );
    }


    std::cout
        << "\nDispatch order:\n";


    while (!dispatchQueue.empty())
    {
        DispatchTrain next =
            dispatchQueue.getNextTrain();


        std::cout
            << next.trainName
            << " | Priority: "
            << next.priority
            << " | Delay: "
            << next.delay
            << " min\n";


        dispatchQueue.removeNextTrain();
    }
}


void MetroController::handleAnalytics()
{
    MetroAnalytics analytics;


    std::vector<int> dailyTrips =
        createDailyTrips();


    std::vector<StationTraffic> traffic =
        createStationTraffic();


    double average =
        analytics.averageDailyTrips(
            dailyTrips
        );


    int k = 3;


    StationTraffic station =
        analytics.kthBusiestStation(
            traffic,
            k
        );


    std::cout
        << "\nAverage daily trips: "
        << average
        << '\n';


    std::cout
        << k
        << "rd busiest station: "
        << station.stationName
        << " | Passengers: "
        << station.passengerCount
        << '\n';
}


void MetroController::handleSimulation()
{
    PassengerSimulator simulator;


    SimulationResult normal =
        simulator.simulate(
            60,
            3,
            4,
            42
        );


    std::cout
        << "\nNormal traffic:\n";

    std::cout
        << "Total passengers: "
        << normal.totalPassengers
        << '\n';

    std::cout
        << "Served passengers: "
        << normal.servedPassengers
        << '\n';

    std::cout
        << "Passengers waiting: "
        << normal.waitingPassengers
        << '\n';

    std::cout
        << "Maximum queue length: "
        << normal.maxQueueLength
        << '\n';

    std::cout
        << "Average wait time: "
        << normal.averageWaitTime
        << " minutes\n";


    SimulationResult peak =
        simulator.simulate(
            60,
            2,
            6,
            42
        );


    std::cout
        << "\nPeak traffic:\n";

    std::cout
        << "Total passengers: "
        << peak.totalPassengers
        << '\n';

    std::cout
        << "Served passengers: "
        << peak.servedPassengers
        << '\n';

    std::cout
        << "Passengers waiting: "
        << peak.waitingPassengers
        << '\n';

    std::cout
        << "Maximum queue length: "
        << peak.maxQueueLength
        << '\n';

    std::cout
        << "Average wait time: "
        << peak.averageWaitTime
        << " minutes\n";
}


void MetroController::handleFloydWarshall()
{
    printStations();


    std::string source;
    std::string destination;
    std::string criterion;


    std::cout
        << "Source: ";

    std::getline(
        std::cin,
        source
    );


    std::cout
        << "Destination: ";

    std::getline(
        std::cin,
        destination
    );


    std::cout
        << "Criterion (distance/time): ";

    std::getline(
        std::cin,
        criterion
    );


    FWPathResult result =
        floyd.shortestPath(
            source,
            destination,
            criterion
        );


    if (!result.found)
    {
        std::cout
            << "\nInvalid input or no path found.\n";

        return;
    }


    std::cout
        << "\nPrecomputed shortest path:\n";

    printPath(result.path);


    std::cout
        << "Cost: "
        << result.cost;


    if (criterion == "distance")
    {
        std::cout << " km\n";
    }
    else
    {
        std::cout << " minutes\n";
    }
}


void MetroController::handleMaxFlow()
{
    int maxFlow =
        flowNetwork.edmondsKarp(
            "Meydan Baghieh Allah",
            "Jamkaran"
        );


    std::cout
        << "\nMaximum passenger flow: "
        << maxFlow
        << " passengers per time unit\n";
}


void MetroController::handleCriticalNetwork()
{
    CriticalNetworkResult result =
        criticalAnalyzer.analyze();


    std::cout
        << "\nArticulation points:\n";


    for (const std::string& station :
         result.articulationPoints)
    {
        std::cout
            << "- "
            << station
            << '\n';
    }


    std::cout
        << "\nBridges:\n";


    for (const Bridge& bridge :
         result.bridges)
    {
        std::cout
            << bridge.first
            << " <-> "
            << bridge.second
            << '\n';
    }
}


void MetroController::handleStationSearch()
{
    std::string input;


    std::cout
        << "Enter station name: ";

    std::getline(
        std::cin,
        input
    );


    StationSearchResult result =
        stationSearch.findClosestStation(
            input
        );


    if (!result.found)
    {
        std::cout
            << "\nNo station found.\n";

        return;
    }


    std::cout
        << "\nClosest station: "
        << result.stationName
        << '\n';


    std::cout
        << "Edit distance: "
        << result.distance
        << '\n';
}


void MetroController::run()
{
    int choice = -1;


    while (choice != 0)
    {
        showMenu();


        if (!(std::cin >> choice))
        {
            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout
                << "\nInvalid input.\n";

            continue;
        }


        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );


        switch (choice)
        {
            case 1:
                printStations();
                break;

            case 2:
                handleReachability();
                break;

            case 3:
                handleDijkstra();
                break;

            case 4:
                handleMST();
                break;

            case 5:
                handleExpressRoute();
                break;

            case 6:
                handleBellmanFord();
                break;

            case 7:
                handleTrainScheduling();
                break;

            case 8:
                handleDispatchQueue();
                break;

            case 9:
                handleAnalytics();
                break;

            case 10:
                handleSimulation();
                break;

            case 11:
                handleFloydWarshall();
                break;

            case 12:
                handleMaxFlow();
                break;

            case 13:
                handleCriticalNetwork();
                break;

            case 14:
                handleStationSearch();
                break;

            case 0:
                std::cout
                    << "\nExiting Qom Metro System...\n";
                break;

            default:
                std::cout
                    << "\nInvalid choice.\n";
        }
    }
}