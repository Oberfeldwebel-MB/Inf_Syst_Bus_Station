#pragma once
#include "ISystemObject.hpp"  // ДОБАВИЛИ
#include <string>
#include <iostream>
#include <memory>

class Bus : public ISystemObject {
private:
    std::string Brand;
    std::string Model;
    int PlaceCount = 0;
    bool BusAvailability = true;
    std::string CodeBus;
    std::string TechSost;
    std::string LastCheckTO;  

public:
    // Конструктор (добавили год выпуска)
    Bus(const std::string& brand,
        const std::string& model,
        int placeCount,
        const std::string& code,
        const std::string& techSost,
        const std::string& lastCheck
        );  


    ~Bus() = default;

    // === РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА ISystemObject ===
    std::string getId() const override;
    std::string getName() const override;
    std::string getType() const override;
    void displayInfo() const override;
    double getSortValue() const override;
    bool containsText(const std::string& text) const override;
    bool isMarkedForRemoval() const override;

    // === СУЩЕСТВУЮЩИЕ МЕТОДЫ Bus ===
    bool CheckAvailBus() const;
    void ChangeAvailBus(bool state);
    void SetTripBus();
    void GoToTO(const std::string& date);
    void Change_sost(const std::string& newState);
    void PrintBusInfo() const;

    // Перегрузка операторов
    bool operator==(const Bus& other) const;
    bool operator!=(const Bus& other) const;
    Bus& operator=(const Bus& other);
    friend std::ostream& operator<<(std::ostream& os, const Bus& bus);

    // Дружественные функции
    friend std::string GetBusFullInfo(const Bus& bus);

    // Геттеры
    std::string GetBrand() const { return this->Brand; }
    std::string GetModel() const { return this->Model; }
    int GetPlaces() const { return this->PlaceCount; }
    bool GetAvailability() const { return this->BusAvailability; }
    std::string GetCode() const { return this->CodeBus; }
    std::string GetTechCondition() const { return this->TechSost; }
    std::string GetLastMaintenance() const { return this->LastCheckTO; }

    // Сеттеры
    void SetBrand(const std::string& newBrand) { this->Brand = newBrand; }
    void SetModel(const std::string& newModel) { this->Model = newModel; }
    void SetPlaceCount(int count) { this->PlaceCount = count; }
    void SetCode(const std::string& code) { this->CodeBus = code; }

    // Для STL алгоритмов сортировки
    bool operator<(const Bus& other) const;
};