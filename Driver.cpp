// Driver.cpp
#include "Driver.hpp"

using namespace InfSystBusStation;

void Driver::PrintInfo() {
    Workers::PrintInfo(); // Вызов метода базового класса
    Console::WriteLine("Категория прав: {0}", driverLicense);
    if (!String::IsNullOrEmpty(currentDriverTrip)) {
        Console::WriteLine("Текущий рейс: {0}", currentDriverTrip);
    }
}

String^ Driver::GetFullInfo() {
    String^ info = "Водитель: " + GetFullName() +
        " | Права: " + driverLicense;

    if (!String::IsNullOrEmpty(currentDriverTrip)) {
        info += " | Рейс: " + currentDriverTrip;
    }
    else {
        info += " | Рейс: Нет";
    }

    return info;
}

double Driver::CalculateDiscount() {
    return 0.15; // 15% скидка для водителей
}