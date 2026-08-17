#ifndef METROOPERATIONS_H
#define METROOPERATIONS_H

#include <string>
#include <vector>
#include <queue>


struct TrainInterval
{
    std::string trainName;
    int arrivalTime;
    int departureTime;
};


struct DispatchTrain
{
    std::string trainName;

    int priority;

    int delay;
};


struct DispatchCompare
{
    bool operator()(const DispatchTrain& first,const DispatchTrain& second) const
    {
        if (first.priority != second.priority)
        {
            return first.priority > second.priority;
        }

        return first.delay < second.delay;
    }
};


class TrainScheduler
{
public:
    std::vector<TrainInterval> selectMaximumTrains(std::vector<TrainInterval> trains) const;
};


class TrainDispatchQueue
{
private:
    std::priority_queue<DispatchTrain,std::vector<DispatchTrain>,DispatchCompare> queue;

public:
    void addTrain(const std::string& trainName,int priority,int delay);

    bool empty() const;

    DispatchTrain getNextTrain() const;

    void removeNextTrain();

    int size() const;
};

struct StationTraffic
{
    std::string stationName;
    int passengerCount;
};


struct StationTrafficCompare
{
    bool operator()(const StationTraffic& first,const StationTraffic& second) const
    {
        return first.passengerCount > second.passengerCount;
    }
};


class MetroAnalytics
{
public:
    double averageDailyTrips(const std::vector<int>& dailyTrips) const;

    StationTraffic kthBusiestStation(const std::vector<StationTraffic>& traffic,int k) const;
};

struct SimulationResult
{
    int totalPassengers;
    int servedPassengers;
    int waitingPassengers;
    int maxQueueLength;
    double averageWaitTime;
};


class PassengerSimulator
{
public:
    SimulationResult simulate(int minutes,int gateCount,int maxArrivalsPerMinute,unsigned int seed = 42) const;
};


#endif