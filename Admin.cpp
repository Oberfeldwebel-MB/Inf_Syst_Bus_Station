#include "Admin.h"
#include "BusList.h"
#include "DriversList.h"
#include "Trip.h"
#include <iostream>


inline void Admin::Change_bus_timing(Timing& timing) {

        std::cout << "=== УПРАВЛЕНИЕ РАСПИСАНИЕМ ===\n";
        std::cout << "1. Показать все поездки\n";
        std::cout << "2. Добавить поездку\n";
        std::cout << "3. Удалить поездку\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            timing.Display_all_trips();
            break;

        case 2: {
            std::cout << "=== ДОБАВЛЕНИЕ ПОЕЗДКИ ===\n";

            std::string start, finish;
            int price;

            std::cout << "Введите пункт отправления: ";
            std::getline(std::cin, start);
            std::cout << "Введите пункт назначения: ";
            std::getline(std::cin, finish);
            std::cout << "Введите цену билета: ";
            std::cin >> price;

            Bus* trip_bus = Chose_bus();
            Driver* trip_driver = Chose_driver();

            Trip newTrip(start, finish, price, trip_bus, trip_driver);
            timing.Add_trip(newTrip); 

            std::cout << "Поездка добавлена!\n";
            break;
        }

        case 3: {
            std::cout << "=== УДАЛЕНИЕ ПОЕЗДКИ ===\n";
            timing.Display_all_trips();
            std::cout << "Для удаления нужно выбрать конкретную поездку...\n";
            std::string start, finish;
            int price;

            std::cout << "Введите пункт отправления: ";
            std::getline(std::cin, start);
            std::cout << "Введите пункт назначения: ";
            std::getline(std::cin, finish);
            std::cout << "Введите цену билета: ";
            std::cin >> price;
            Bus* trip_bus = Chose_bus();
            Driver* trip_driver = Chose_driver();
            break;
        }

        case 0:
            std::cout << "Выход из управления расписанием\n";
            break;

        default:
            std::cout << "Неверный выбор!\n";
            break;
        }
 }


inline Bus* Admin::Chose_bus(){
	std::string Selected_code_bus;
	BusList busList;
	busList.Display_All_Buses(); 
	std::cout << "Введите код автобуса: ";
	std::cin >> Selected_code_bus;
	Bus* foundBus = busList.Find_Bus_By_Code(Selected_code_bus);
	if (foundBus != nullptr) {
		std::cout << " Найден автобус : " << foundBus->GetBrand()
			<< " " << foundBus->GetModel() << "\n";
        return foundBus;
	}
	else {
		std::cout << " Автобус с кодом '" << Selected_code_bus << "' не найден!\n";
	}
}

inline Driver* Admin::Chose_driver() {
	std::string Selected_driver_name;
	DriverList driverList;
	driverList.DisplayAllDrivers();
	std::cout << "Введите ФИО водителя: ";

	std::getline(std::cin, Selected_driver_name);

	Driver* found_Driver = driverList.FindDriverByName(Selected_driver_name);

	if (found_Driver != nullptr) {
		std::cout << " Найден водитель: " << found_Driver->GetFullName()
			<< " (Права: " << found_Driver->GetLicense() << ")\n";
	}
	else {
		std::cout << "Водитель '" << Selected_driver_name << "' не найден!\n";
	}
}

