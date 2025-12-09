#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <string>
#include "Trip.hpp"

class Timing {
private:
    std::vector<std::shared_ptr<Trip>> tripList;

    std::map<std::string, std::string> stringData;    // для строк
    std::map<std::string, int> intData;               // для целых чисел
    std::map<std::string, double> doubleData;         // для дробных чисел

public:
    Timing() = default;
    ~Timing() = default;

    // Конструктор копирования
    Timing(const Timing& other) {
        for (const auto& trip : other.tripList) {
            // новые копии поездок
            tripList.push_back(std::make_shared<Trip>(*trip));
        }
        // Копируем дополнительные данные
        stringData = other.stringData;
        intData = other.intData;
        doubleData = other.doubleData;
    }

    // Управление расписанием
    std::shared_ptr<Trip> ChoseTrip();
    void AddTrip(std::shared_ptr<Trip> trip);
    bool RemoveTrip(const std::string& route);
    void DisplayAllTrips() const;
    void DisplayActiveTrips() const;
    void DisplayCompletedTrips() const;
    void DisplayPlannedTrips() const;

    // Геттеры
    std::vector<std::shared_ptr<Trip>>& GetTripList() { return tripList; }
    const std::vector<std::shared_ptr<Trip>>& GetTripList() const { return tripList; }

    
    void addStringData(const std::string& key, const std::string& value) {
        stringData[key] = value;
    }

    void addIntData(const std::string& key, int value) {
        intData[key] = value;
    }

    void addDoubleData(const std::string& key, double value) {
        doubleData[key] = value;
    }

    std::string getStringData(const std::string& key) const {
        auto it = stringData.find(key);
        return it != stringData.end() ? it->second : "";
    }

    int getIntData(const std::string& key) const {
        auto it = intData.find(key);
        return it != intData.end() ? it->second : 0;
    }

    double getDoubleData(const std::string& key) const {
        auto it = doubleData.find(key);
        return it != doubleData.end() ? it->second : 0.0;
    }
};