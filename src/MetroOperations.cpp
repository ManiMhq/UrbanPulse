#include "MetroOperations.h"

#include <algorithm>
#include <stdexcept>
#include <random>


std::vector<TrainInterval>
TrainScheduler::selectMaximumTrains(std::vector<TrainInterval> trains) const
{
    std::sort(
        trains.begin(),
        trains.end(),
        [](const TrainInterval& first,
           const TrainInterval& second)
        {
            if (first.departureTime !=
                second.departureTime)
            {
                return first.departureTime <
                       second.departureTime;
            }

            return first.arrivalTime <
                   second.arrivalTime;
        }
    );

    std::vector<TrainInterval> selected;

    int lastDeparture = -1;

    for (const TrainInterval& train : trains)
    {
        if (train.arrivalTime >= lastDeparture)
        {
            selected.push_back(train);

            lastDeparture = train.departureTime;
        }
    }

    return selected;
}


void TrainDispatchQueue::addTrain(const std::string& trainName,int priority,int delay
)
{
    queue.push({trainName,priority,delay});
}


bool TrainDispatchQueue::empty() const
{
    return queue.empty();
}


DispatchTrain
TrainDispatchQueue::getNextTrain() const
{
    if (queue.empty())
    {
        throw std::runtime_error("Dispatch queue is empty.");
    }

    return queue.top();
}


void TrainDispatchQueue::removeNextTrain()
{
    if (!queue.empty())
    {
        queue.pop();
    }
}


int TrainDispatchQueue::size() const
{
    return static_cast<int>(queue.size());
}

double MetroAnalytics::averageDailyTrips(const std::vector<int>& dailyTrips) const
{
    if (dailyTrips.empty())
    {
        throw std::invalid_argument("Daily trips list cannot be empty.");
    }

    long long total = 0;

    for (int trips : dailyTrips)
    {
        total += trips;
    }

    return static_cast<double>(total) / dailyTrips.size();
}


StationTraffic MetroAnalytics::kthBusiestStation(const std::vector<StationTraffic>& traffic,int k) const
{
    if (k <= 0 || k > static_cast<int>(traffic.size()))
    {
        throw std::invalid_argument("Invalid value of k.");
    }

    std::priority_queue<StationTraffic,std::vector<StationTraffic>,StationTrafficCompare> minHeap;

    for (const StationTraffic& station : traffic)
    {
        minHeap.push(station);

        if (static_cast<int>(minHeap.size()) > k)
        {
            minHeap.pop();
        }
    }

    return minHeap.top();
}

SimulationResult PassengerSimulator::simulate(int minutes,int gateCount,int maxArrivalsPerMinute,unsigned int seed) const
{
    if (minutes <= 0 || gateCount <= 0 || maxArrivalsPerMinute < 0)
    {
        throw std::invalid_argument("Invalid simulation parameters.");
    }

    std::mt19937 randomGenerator(seed);

    std::uniform_int_distribution<int>arrivalDistribution(0,maxArrivalsPerMinute);

    std::queue<int> passengerQueue;

    int totalPassengers = 0;
    int servedPassengers = 0;
    int maxQueueLength = 0;

    long long totalWaitTime = 0;


    for (int minute = 0;minute < minutes;minute++)
    {
        int newPassengers =arrivalDistribution(randomGenerator);
        
        for (int i = 0;i < newPassengers;i++)
        {
            passengerQueue.push(minute);

            totalPassengers++;
        }


        if (static_cast<int>(passengerQueue.size()) >maxQueueLength)
        {
            maxQueueLength = static_cast<int>(passengerQueue.size());
        }


        for (int gate = 0;gate < gateCount &&!passengerQueue.empty();gate++)
        {
            int arrivalTime =passengerQueue.front();passengerQueue.pop();

            int waitTime =minute - arrivalTime;

            totalWaitTime += waitTime;

            servedPassengers++;
        }
    }


    double averageWaitTime = 0;

    if (servedPassengers > 0)
    {
        averageWaitTime =static_cast<double>(totalWaitTime) / servedPassengers;
    }


    return {totalPassengers, servedPassengers, static_cast<int>(passengerQueue.size()),maxQueueLength,averageWaitTime};
}
