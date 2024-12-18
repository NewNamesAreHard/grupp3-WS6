#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
}

Sensor::~Sensor()
{
    Running = false;
}

float Sensor::calculateAverage()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return (std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
}

float Sensor::calculateMinimum()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return *std::min_element(dataList.begin(), dataList.end());
}

float Sensor::calculateMaximum()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return *std::max_element(dataList.begin(), dataList.end());
}

float Sensor::getLatestData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return 0.0; // <-- To remove warnings
}

float Sensor::getAverageData()
{
    return calculateAverage();
}

float Sensor::getMinimumData()
{
    return calculateMinimum();
}

float Sensor::getMaxData()
{
    return calculateMaximum();
}

float Sensor::generateRandomSensorData(float minValue, float maxValue) 
{
    std::uniform_real_distribution<> dist(minValue, maxValue);
    return dist(mt);
}