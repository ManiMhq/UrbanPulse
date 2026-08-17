#include "Data.h"


MetroGraph createQomMetroGraph()
{
    MetroGraph graph;

    graph.addRoute(
        "Terminal",
        "Qale Kamkar",
        1.2,
        3
    );

    graph.addRoute(
        "Qale Kamkar",
        "Meydan Keshavarz",
        2.5,
        5
    );

    graph.addRoute(
        "Meydan Keshavarz",
        "Meydan Motahhari",
        6,
        10
    );

    graph.addRoute(
        "Meydan Motahhari",
        "Nekoee Hospital",
        3,
        5
    );

    graph.addRoute(
        "Nekoee Hospital",
        "Meydan Baghieh Allah",
        2,
        4
    );

    graph.addRoute(
        "Meydan Baghieh Allah",
        "Jamkaran",
        3.8,
        6
    );

    graph.addRoute(
        "Meydan Motahhari",
        "Haram",
        1.5,
        4
    );

    graph.addRoute(
        "Haram",
        "Arg Salarieh",
        1,
        3
    );

    graph.addRoute(
        "Haram",
        "Darvazeh Rey",
        1.8,
        4
    );

    graph.addRoute(
        "Darvazeh Rey",
        "Bajak",
        1.3,
        3
    );

    graph.addRoute(
        "Meydan Motahhari",
        "Niroogah",
        2.8,
        5
    );

    graph.addRoute(
        "Niroogah",
        "Sadeghieh",
        1.5,
        3
    );

    graph.addRoute(
        "Sadeghieh",
        "Chehel Derakht",
        1.7,
        3
    );

    graph.addRoute(
        "Chehel Derakht",
        "Amin Abad",
        1.4,
        3
    );

    graph.addRoute(
        "Niroogah",
        "Amin Abad",
        2,
        4
    );

    graph.addRoute(
        "Meydan Baghieh Allah",
        "Pardisan",
        5,
        8
    );

    graph.addRoute(
        "Pardisan",
        "Qom University",
        2.2,
        4
    );

    graph.addRoute(
        "Pardisan",
        "Ghadir Forest Park",
        3.5,
        6
    );

    graph.addRoute(
        "Haram",
        "Fadak Park",
        2.4,
        4
    );

    graph.addRoute(
        "Qale Kamkar",
        "Qom Railway",
        3,
        5
    );

    graph.addRoute(
        "Qom University",
        "Jamkaran",
        4.5,
        7
    );

    return graph;
}


ExpressNetwork createExpressNetwork()
{
    ExpressNetwork network;

    network.addDirectedRoute(
        "Terminal",
        "Qale Kamkar",
        1.2
    );

    network.addDirectedRoute(
        "Qale Kamkar",
        "Meydan Keshavarz",
        2.5
    );

    network.addDirectedRoute(
        "Meydan Keshavarz",
        "Meydan Motahhari",
        6
    );

    network.addDirectedRoute(
        "Meydan Motahhari",
        "Nekoee Hospital",
        3
    );

    network.addDirectedRoute(
        "Nekoee Hospital",
        "Meydan Baghieh Allah",
        2
    );

    network.addDirectedRoute(
        "Meydan Baghieh Allah",
        "Jamkaran",
        3.8
    );

    network.addDirectedRoute(
        "Meydan Motahhari",
        "Haram",
        1.5
    );

    network.addDirectedRoute(
        "Meydan Baghieh Allah",
        "Pardisan",
        5
    );

    network.addDirectedRoute(
        "Pardisan",
        "Qom University",
        2.2
    );

    network.addDirectedRoute(
        "Qom University",
        "Jamkaran",
        4.5
    );

    return network;
}


BellmanFordNetwork createBellmanFordNetwork()
{
    BellmanFordNetwork network;

    network.addDirectedEdge(
        "Terminal",
        "Qale Kamkar",
        1.2
    );

    network.addDirectedEdge(
        "Qale Kamkar",
        "Meydan Keshavarz",
        2.5
    );

    network.addDirectedEdge(
        "Meydan Keshavarz",
        "Meydan Motahhari",
        6
    );

    network.addDirectedEdge(
        "Meydan Motahhari",
        "Nekoee Hospital",
        3
    );

    network.addDirectedEdge(
        "Nekoee Hospital",
        "Meydan Baghieh Allah",
        2
    );

    network.addDirectedEdge(
        "Meydan Baghieh Allah",
        "Jamkaran",
        3.8
    );

    network.addDirectedEdge(
        "Meydan Motahhari",
        "Jamkaran",
        -2
    );

    return network;
}


FlowNetwork createFlowNetwork()
{
    FlowNetwork network;

    network.addDirectedRoute(
        "Meydan Baghieh Allah",
        "Jamkaran",
        70
    );

    network.addDirectedRoute(
        "Meydan Baghieh Allah",
        "Pardisan",
        50
    );

    network.addDirectedRoute(
        "Pardisan",
        "Qom University",
        40
    );

    network.addDirectedRoute(
        "Qom University",
        "Jamkaran",
        35
    );

    return network;
}


std::vector<TrainInterval> createTrainIntervals()
{
    return {
        {"Train A", 1, 4},
        {"Train B", 3, 5},
        {"Train C", 0, 6},
        {"Train D", 5, 7},
        {"Train E", 3, 9},
        {"Train F", 5, 9},
        {"Train G", 6, 10},
        {"Train H", 8, 11},
        {"Train I", 8, 12},
        {"Train J", 2, 14},
        {"Train K", 12, 16}
    };
}


std::vector<DispatchTrain> createDispatchTrains()
{
    return {
        {"Train 101", 3, 5},
        {"Train 202", 1, 2},
        {"Train 303", 2, 10},
        {"Train 404", 1, 15}
    };
}


std::vector<int> createDailyTrips()
{
    return {
        1200,
        1350,
        1280,
        1420,
        1500,
        1380,
        1470
    };
}


std::vector<StationTraffic> createStationTraffic()
{
    return {
        {"Terminal", 3000},
        {"Haram", 5200},
        {"Jamkaran", 4100},
        {"Pardisan", 2800},
        {"Qom University", 3400}
    };
}