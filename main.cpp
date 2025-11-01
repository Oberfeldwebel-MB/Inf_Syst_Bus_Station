#include "DriversList.hpp"
#include "People.hpp"
#include "Passenger.hpp"
#include "Workers.hpp"
#include "Driver.hpp"
#include "Admin.hpp"
#include "Bus.hpp"
#include "BusList.hpp"
#include "Trip.hpp"
#include "Timing.hpp"
#include "Ticket.hpp"
#include "TicketChose.hpp"
#include "Order.hpp"
#include "Search.hpp"
#include "User.hpp"
#include <windows.h>
#include <iostream>
#include <vector>


using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // 1. Статическая инициализация объектов
    cout << "1. Статическая инициализация объектов:\n";
    cout << "----------------------------------------\n";

    Bus staticBus("Mercedes", "Sprinter", 25, "BUS001");
    Driver staticDriver("Клевакин", "Ярослав", "Максимович", 85000, "D123456");
    Passenger staticPassenger("Иванов", "Иван", "Иванович", "1234", "567890", "ivanov@mail.ru");

    cout << "Созданы статические объекты:\n";
    staticBus.PrintBusInfo();
    cout << "Водитель: " << staticDriver.GetFullName() << "\n";
    cout << "Пассажир: " << staticPassenger.GetFullName() << "\n\n";

    // 2. ДИинамическая инициализация (new/delete)
    cout << "2. ДИинамическая инициализация (new/delete):\n";
    cout << "--------------------------------------------\n";

    Bus* dynamicBus = new Bus("Volvo", "Intercity", 40, "BUS002");
    Driver* dynamicDriver = new Driver("Струков", "Руслан", "Владимирович", 50000, "D654321");
    Admin* dynamicAdmin = new Admin("Румянцев", "Максим", "Станиславович", 60000);

    cout << "Созданы динамические объекты:\n";
    dynamicBus->PrintBusInfo();
    cout << "Водитель: " << dynamicDriver->GetFullName() << "\n";
    cout << "Администратор: " << dynamicAdmin->GetFullName() << "\n\n";

    // 3. Работа с ссылками и указателями
    cout << "3. РАБОТА С ССЫЛКАМИ И УКАЗАТЕЛЯМИ:\n";
    cout << "-----------------------------------\n";

    // Работа со ссылками
    Bus& busRef = *dynamicBus;
    Driver& driverRef = *dynamicDriver;

    cout << "Работа со ссылками:\n";
    cout << "- Автобус через ссылку: " << busRef.GetModel() << "\n";
    cout << "- Водитель через ссылку: " << driverRef.GetLicense() << "\n";

    // Работа с указателями
    Bus* busPtr = dynamicBus;
    Driver* driverPtr = dynamicDriver;

    cout << "Работа с указателями:\n";
    cout << "- Автобус через указатель: " << busPtr->GetBrand() << "\n";
    cout << "- Водитель через указатель: " << driverPtr->GetFullName() << "\n\n";

    // 4. Динамический массив объектов класса
    cout << "4. Динамический массив объектов класса:\n";
    cout << "---------------------------------------\n";

    Bus busArray[2] = {
        Bus("MAN", "Lion", 35, "BUS101"),
        Bus("Scania", "Interlink", 45, "BUS102")
    };

    cout << "Массив автобусов:\n";
    for (int i = 0; i < 2; i++) {
        cout << "- " << busArray[i].GetBrand() << " [" << busArray[i].GetCode() << "]\n";
    }
    cout << "\n";

    // 5. Массив динамических объектов класса
    cout << "5. Массив динамических объектов класса:\n";
    cout << "---------------------------------------\n";

    Driver* driverArray[2] = {
        new Driver("Ганюшкин", "Константин", "Владимирович", 48000, "D111111"),
        new Driver("Валяев", "Федор", "Сергеевич", 52000, "D222222")
    };

    cout << "Массив динамических водителей:\n";
    for (int i = 0; i < 2; i++) {
        cout << "- " << driverArray[i]->GetFullName() << " (" << driverArray[i]->GetLicense() << ")\n";
    }
    cout << "\n";

    // 6. Освобождение памяти
    cout << "6. Освобождение памяти (delete):\n";
    cout << "---------------------------------\n";

    delete dynamicBus;
    delete dynamicDriver;
    delete dynamicAdmin;

    for (int i = 0; i < 2; i++) {
        delete driverArray[i];
    }

    cout << "Динамическая память освобождена.\n\n";

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.get();  // Ждет нажатия Enter

    return 0;
}
