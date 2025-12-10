// DriversList.cpp
#include "DriversList.hpp"
#include <algorithm>
#include <vector>
#include <msclr/marshal_cppstd.h>

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

// Конструктор
DriversList::DriversList() {
    drivers = gcnew List<Driver^>();
}

// Деструктор
DriversList::~DriversList() {
    drivers->Clear();
}

// Добавление уже созданного водителя
void DriversList::AddDriver(Driver^ driver) {
    if (driver == nullptr) {
        throw gcnew ArgumentNullException("Нельзя добавить пустую ссылку на водителя!");
    }

    // Проверка на дубликат по ФИО - используем foreach
    for each (Driver ^ existingDriver in drivers) {
        if (existingDriver->GetFullName() == driver->GetFullName()) {
            throw gcnew InvalidOperationException("Водитель с таким ФИО уже существует!");
        }
    }

    drivers->Add(driver);
    Console::WriteLine("Водитель {0} добавлен.", driver->GetFullName());
}

// Создание и добавление водителя из данных
void DriversList::AddDriver(String^ fullName, int salary, String^ gender,
    String^ license, String^ passportSeries,
    String^ passportNumber) {
    Driver^ driver = gcnew Driver(fullName, gender, passportSeries,
        passportNumber, salary, license);
    AddDriver(driver);
}

// Поиск водителя по ФИО
Driver^ DriversList::FindDriverByName(String^ fullName) {
    for each (Driver ^ driver in drivers) {
        if (driver->GetFullName() == fullName) {
            return driver;
        }
    }
    return nullptr;
}

// Удаление водителя
bool DriversList::RemoveDriver(String^ fullName) {
    for (int i = 0; i < drivers->Count; i++) {
        if (drivers[i]->GetFullName() == fullName) {
            drivers->RemoveAt(i);
            Console::WriteLine("Водитель {0} удален.", fullName);
            return true;
        }
    }
    return false;
}

// Вывод всех водителей
void DriversList::DisplayAllDrivers() {
    Console::WriteLine("=== Список водителей ({0}) ===", drivers->Count);
    for each (Driver ^ driver in drivers) {
        driver->PrintInfo();
        Console::WriteLine("---");
    }
    Console::WriteLine("=================================");
}

// Получение всех водителей
List<Driver^>^ DriversList::AllDrivers::get() {
    return drivers;
}

// Количество водителей
int DriversList::Count::get() {
    return drivers->Count;
}