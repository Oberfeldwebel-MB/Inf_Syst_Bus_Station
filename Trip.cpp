#include "Trip.hpp"
#include "iostream"


void Trip::Start_trip() {
    StatusTrip = "В пути";
    std::cout << "Поездка началась: " << StartPoint << " - " << FinishPoint << "\n";
    std::cout << "Водитель: " << DriverData->GetFullName() << "\n";
    std::cout << "Автобус: " << BusData->GetBrand() << " [" << BusData->GetCode() << "]\n";
}

void Trip::Complete_trip() {
    StatusTrip = "Завершена";
    std::cout << "Поездка завершена : " << StartPoint << " - " << FinishPoint << "\n";
}

void Trip::Cancel_trip() {
    StatusTrip = "Отменена";
    std::cout << "Поездка отменена: " << StartPoint << " - " << FinishPoint << "\n";
}

void Trip::Print_trip_info() const {
    std::cout << "=== Информация о поездке ===\n";
    std::cout << "Маршрут: " << StartPoint << " → " << FinishPoint << "\n";
    std::cout << "Статус: " << StatusTrip << "\n";
    std::cout << "Цена билета: " << PriceTicket << " руб.\n";
    std::cout << "Автобус: " << BusData->GetBrand() << " [" << BusData->GetCode() << "]\n";
    std::cout << "Водитель: " << DriverData->GetFullName() << "\n";
    std::cout << "=============================\n";
}

void Trip::Change_driver(DriverList& driverList) {
    //список доступных водителей
    std::cout << "=== Доступные водители ===\n";

    bool foundAvailable = false;
    for (const auto& driver : driverList.GetDrivers()) {
        if (driver.GetAvailability()) {
            std::cout << "• " << driver.GetFullName()
                << " (Права: " << driver.GetLicense() << ")\n";
            foundAvailable = true;
        }
    }

    if (!foundAvailable) {
        std::cout << "Нет доступных водителей!\n";
        return;
    }

    std::string selectedName;
    std::cout << "Введите ФИО водителя: ";
    std::getline(std::cin, selectedName);

    //поиск и установка водителя
    Driver* foundDriver = driverList.FindDriverByName(selectedName);
    if (foundDriver && foundDriver->GetAvailability()) {
        DriverData = foundDriver;
        std::cout << "Водитель изменен на: " << foundDriver->GetFullName() << "\n";

        // Автоматически меняем статус водителя на "занят"
        (*foundDriver).change_work_avail(false);
    }
    else {
        std::cout << "Водитель не найден или недоступен!\n";
    }
}
    
void Trip::Change_bus(BusList & busList) {
        //  список доступных автобусов
        std::cout << "=== Доступные автобусы ===\n";

        bool foundAvailable = false;
        for (const auto& bus : busList.GetBuses()) {
            if (bus.GetAvailability()) {
                std::cout << "• [" << bus.GetCode() << "] " << bus.GetBrand()
                    << " " << bus.GetModel() << " (" << bus.GetPlaces() << " мест)\n";
                foundAvailable = true;
            }
        }

        if (!foundAvailable) {
            std::cout << "Нет доступных автобусов!\n";
            return;
        }

        // Выбор автобуса
        std::string selectedCode;
        std::cout << "Введите код автобуса: ";
        std::cin >> selectedCode;

        // Поиск и установка автобуса
        Bus* foundBus = busList.FindBusByCode(selectedCode);
        if (foundBus && foundBus->GetAvailability()) {
            BusData = foundBus;
            std::cout << "Автобус изменен на: " << foundBus->GetBrand()
                << " [" << foundBus->GetCode() << "]\n";

            //Изменение статуса автобуса на "недоступен"
            foundBus->ChangeAvailBus(false);
        }
        else {
            std::cout << "Автобус не найден или недоступен!\n";
        }
}
