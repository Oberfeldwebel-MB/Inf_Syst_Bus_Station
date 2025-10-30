#pragma once
#include <string>

class Bus {
private:
    std::string Brand;
    std::string Model;
    int Place_count = 0;
    bool Bus_availability = true;
    std::string Code_bus;
    std::string Tech_sost;
    std::string Last_check_TO;

public:
    Bus(const std::string& brand = "",
        const std::string& model = "",
        int place_count = 0,
        const std::string& code = "",
        const std::string& tech_sost = "",
        const std::string& lastCheck = "")
        : Brand(brand), Model(model), Place_count(place_count),
        Code_bus(code), Tech_sost(tech_sost), Last_check_TO(lastCheck) {
    }
    ~Bus() = default;

    // методы класса
    bool Check_avail_bus();
    void Change_avail_bus(bool state);
    void Set_trip_bus();
    void Go_to_TO(std::string& date);  
    void Change_sost(std::string& newState);
    void Print_Bus_info();

    // методы для изменения полей (сеттеры)
    void SetBrand(std::string& newBrand) 
        { Brand = newBrand; }
    void SetModel(std::string& newModel) 
        { Model = newModel; }
    void SetPlaceCount(int count) 
        { Place_count = count; }

    // Методы для получения данных из переменных (геттеры)
    std::string GetBrand() const { return Brand; }
    std::string GetModel() const { return Model; }
    int GetPlaces() const { return Place_count; }
    bool GetAvailability() const { return Bus_availability; }
    std::string GetCode() const { return Code_bus; }
};