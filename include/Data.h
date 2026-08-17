#ifndef DATA_H
#define DATA_H

#include "MetroGraph.h"
#include "ExpressNetwork.h"
#include "BellmanFord.h"
#include "MetroOperations.h"
#include "NetworkAnalysis.h"

#include <vector>


MetroGraph createQomMetroGraph();

ExpressNetwork createExpressNetwork();

BellmanFordNetwork createBellmanFordNetwork();

FlowNetwork createFlowNetwork();

std::vector<TrainInterval> createTrainIntervals();

std::vector<DispatchTrain> createDispatchTrains();

std::vector<int> createDailyTrips();

std::vector<StationTraffic> createStationTraffic();


#endif