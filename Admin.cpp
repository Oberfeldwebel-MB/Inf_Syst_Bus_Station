#include "Admin.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "Trip.hpp"
#include <iostream>


inline void Admin::ChangeBusTiming(Timing& timing) {

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
            timing.DisplayAllTrips();
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

            Bus* tripBus = ChoseBus();
            Driver* tripDriver = ChoseDriver();

            Trip newTrip(start, finish, price, tripBus, tripDriver);
            timing.AddTrip(newTrip); 

            std::cout << "Поездка добавлена!\n";
            break;
        }

        case 3: {
            std::cout << "=== УДАЛЕНИЕ ПОЕЗДКИ ===\n";
            timing.DisplayAllTrips();
            std::cout << "Для удаления нужно выбрать конкретную поездку...\n";
            std::string start, finish;
            int price;

            std::cout << "Введите пункт отправления: ";
            std::getline(std::cin, start);
            std::cout << "Введите пункт назначения: ";
            std::getline(std::cin, finish);
            std::cout << "Введите цену билета: ";
            std::cin >> price;
            Bus* tripBus = ChoseBus();
            Driver* tripDriver = ChoseDriver();
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


inline Bus* Admin::ChoseBus(){
	std::string SelectedCodeBus;
	BusList busList;
	busList.DisplayAllBuses(); 
	std::cout << "Введите код автобуса: ";
	std::cin >> SelectedCodeBus;
	Bus* foundBus = busList.FindBusByCode(SelectedCodeBus);
	if (foundBus != nullptr) {
		std::cout << " Найден автобус : " << foundBus->GetBrand()
			<< " " << foundBus->GetModel() << "\n";
        return foundBus;
	}
	else {
		std::cout << " Автобус с кодом '" << SelectedCodeBus << "' не найден!\n";
	}
}

inline Driver* Admin::ChoseDriver() {
	std::string SelectedDriverName;
	DriverList driverList;
	driverList.DisplayAllDrivers();
	std::cout << "Введите ФИО водителя: ";

	std::getline(std::cin, SelectedDriverName);

	Driver* foundDriver = driverList.FindDriverByName(SelectedDriverName);

	if (foundDriver != nullptr) {
		std::cout << " Найден водитель: " << foundDriver->GetFullName()
			<< " (Права: " << foundDriver->GetLicense() << ")\n";
	}
	else {
		std::cout << "Водитель '" << SelectedDriverName << "' не найден!\n";
	}
}

