#include "Trip.h"
#include "iostream"


void Trip::Start_trip() {
    Status_tr = "В пути";
    std::cout << "Поездка началась: " << Start_point << " - " << Finish_point << "\n";
    std::cout << "Водитель: " << Driver_data->GetFullName() << "\n";
    std::cout << "Автобус: " << Bus_data->GetBrand() << " [" << Bus_data->GetCode() << "]\n";
}

void Trip::Complete_trip() {
    Status_tr = "Завершена";
    std::cout << "Поездка завершена : " << Start_point << " - " << Finish_point << "\n";
}

void Trip::Cancel_trip() {
    Status_tr = "Отменена";
    std::cout << "Поездка отменена: " << Start_point << " - " << Finish_point << "\n";
}

void Trip::Print_trip_info() const {
    std::cout << "=== Информация о поездке ===\n";
    std::cout << "Маршрут: " << Start_point << " → " << Finish_point << "\n";
    std::cout << "Статус: " << Status_tr << "\n";
    std::cout << "Цена билета: " << Price_tick << " руб.\n";
    std::cout << "Автобус: " << Bus_data->GetBrand() << " [" << Bus_data->GetCode() << "]\n";
    std::cout << "Водитель: " << Driver_data->GetFullName() << "\n";
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
        Driver_data = foundDriver;
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
        Bus* foundBus = busList.Find_Bus_By_Code(selectedCode);
        if (foundBus && foundBus->GetAvailability()) {
            Bus_data = foundBus;
            std::cout << "Автобус изменен на: " << foundBus->GetBrand()
                << " [" << foundBus->GetCode() << "]\n";

            //Изменение статуса автобуса на "недоступен"
            foundBus->Change_avail_bus(false);
        }
        else {
            std::cout << "Автобус не найден или недоступен!\n";
        }
}
