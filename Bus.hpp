#pragma once
#include <string>

class Bus {
private:
    std::string Brand;
    std::string Model;
    int PlaceCount = 0;
    bool BusAvailability = true;
    std::string CodeBus;
    std::string TechSost;
    std::string LastCheckTO;

public:
    Bus(const std::string& brand = "",
        const std::string& model = "",
        int placeCount = 0,
        const std::string& code = "",
        const std::string& techSost = "",
        const std::string& lastCheck = "")
        : Brand(brand), Model(model), PlaceCount(placeCount),
        CodeBus(code), TechSost(techSost), LastCheckTO(lastCheck) {
    }
    ~Bus() = default;

    // методы класса
    bool CheckAvailBus();
    void ChangeAvailBus(bool state);
    void SetTripBus();
    void GoToTO(std::string& date);  
    void Change_sost(std::string& newState);
    void PrintBusInfo();

    // методы для изменения полей (сеттеры)
    void SetBrand(std::string& newBrand) 
        { Brand = newBrand; }
    void SetModel(std::string& newModel) 
        { Model = newModel; }
    void SetPlaceCount(int count) 
        { PlaceCount = count; }

    // Методы для получения данных из переменных (геттеры)
    std::string GetBrand() const { return Brand; }
    std::string GetModel() const { return Model; }
    int GetPlaces() const { return PlaceCount; }
    bool GetAvailability() const { return BusAvailability; }
    std::string GetCode() const { return CodeBus; }
};