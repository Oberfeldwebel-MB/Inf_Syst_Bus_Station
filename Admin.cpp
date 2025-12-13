// Admin.cpp
#include "Admin.hpp"
#include "DriversListForm.h"
#include "AddDriverForm.h"
#include "DeleteDriverForm.h"
#include "BusListForm.h"
#include "AddBusForm.h"
#include "DeleteBusForm.h"
#include "TimingForm.h"
#include "AddTripForm.h"
#include "DeleteTripForm.h"
#include "EditTripForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор
Admin::Admin() {
    driversList = gcnew DriversList();
    busList = gcnew BusList();
    tripList = gcnew TripList();
}

// Деструктор
Admin::~Admin() {
    // Автоматическое управление памятью в C++/CLI
}

// Инициализация
void Admin::Initialize() {
    // Можно добавить загрузку начальных данных из файла/БД
    Console::WriteLine("[Admin] Система инициализирована");
}

// === МЕТОДЫ ДЛЯ ВОДИТЕЛЕЙ ===

bool Admin::AddDriver(String^ fio, String^ gender, String^ passportSeries,
    String^ passportNumber, int salary, String^ license) {
    try {
        // Валидация
        if (String::IsNullOrEmpty(fio)) {
            throw gcnew ArgumentException("ФИО не может быть пустым!");
        }

        if (salary <= 0) {
            throw gcnew ArgumentException("Зарплата должна быть положительной!");
        }

        if (String::IsNullOrEmpty(license)) {
            throw gcnew ArgumentException("Номер прав не может быть пустым!");
        }

        // Создание водителя
        Driver^ newDriver = gcnew Driver(fio, gender, passportSeries,
            passportNumber, salary, license);

        // Добавление через DriversList
        driversList->AddDriver(newDriver);
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении водителя: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::RemoveDriver(String^ fio) {
    try {
        return driversList->RemoveDriver(fio);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении водителя: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::EditDriver(String^ oldFio, String^ newFio, String^ newGender,
    String^ newPassportSeries, String^ newPassportNumber,
    int newSalary, String^ newLicense) {
    try {
        // Находим водителя
        Driver^ driver = driversList->FindDriverByName(oldFio);
        if (driver == nullptr) {
            MessageBox::Show("Водитель не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Обновляем данные
        if (!String::IsNullOrEmpty(newFio)) {
            driver->SetFullName(newFio);
        }

        if (!String::IsNullOrEmpty(newGender)) {
            driver->SetGender(newGender);
        }

        if (!String::IsNullOrEmpty(newPassportSeries) && !String::IsNullOrEmpty(newPassportNumber)) {
            driver->SetPassportSeries(newPassportSeries);
            driver->SetPassportNumber(newPassportNumber);
        }

        if (newSalary > 0) {
            driver->SetSalary(newSalary);
        }

        if (!String::IsNullOrEmpty(newLicense)) {
            driver->SetLicense(newLicense);
        }

        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при редактировании водителя: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

Driver^ Admin::FindDriver(String^ fio) {
    return driversList->FindDriverByName(fio);
}

bool Admin::IsDriverAvailable(String^ fio) {
    Driver^ driver = FindDriver(fio);
    return driver != nullptr && driver->GetAvailability();
}

// === МЕТОДЫ ДЛЯ АВТОБУСОВ ===

bool Admin::AddBus(String^ brand, String^ model, int placeCount,
    String^ code, String^ techCondition, String^ lastMaintenance) {
    try {
        return busList->InternalAddBus(brand, model, placeCount, code,
            techCondition, lastMaintenance);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::RemoveBus(String^ code) {
    try {
        return busList->InternalRemoveBus(code);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::EditBus(String^ oldCode, String^ newBrand, String^ newModel,
    int newPlaceCount, String^ newTechCondition, String^ newLastMaintenance) {
    try {
        Bus^ bus = busList->FindBusByCode(oldCode);
        if (bus == nullptr) {
            MessageBox::Show("Автобус не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Обновляем данные
        if (!String::IsNullOrEmpty(newBrand)) {
            bus->SetBrand(newBrand);
        }

        if (!String::IsNullOrEmpty(newModel)) {
            bus->SetModel(newModel);
        }

        if (newPlaceCount > 0) {
            bus->SetPlaceCount(newPlaceCount);
        }

        if (!String::IsNullOrEmpty(newTechCondition)) {
            bus->SetTechCondition(newTechCondition);
        }

        if (!String::IsNullOrEmpty(newLastMaintenance)) {
            bus->SetLastMaintenance(newLastMaintenance);
        }

        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при редактировании автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

Bus^ Admin::FindBus(String^ code) {
    return busList->FindBusByCode(code);
}

bool Admin::IsBusAvailable(String^ code) {
    Bus^ bus = FindBus(code);
    return bus != nullptr && bus->GetAvailability() && !bus->IsInCriticalCondition();
}

// === МЕТОДЫ ДЛЯ ПОЕЗДОК ===

bool Admin::AddTrip(String^ startPoint, String^ finishPoint, int price,
    String^ busCode, String^ driverFio,
    DateTime depDate, String^ depTime) {
    try {
        // Находим автобус и водителя
        Bus^ bus = FindBus(busCode);
        Driver^ driver = FindDriver(driverFio);

        if (bus == nullptr) {
            MessageBox::Show("Автобус не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (driver == nullptr) {
            MessageBox::Show("Водитель не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Проверяем доступность
        if (!bus->GetAvailability()) {
            MessageBox::Show("Выбранный автобус недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (!driver->GetAvailability()) {
            MessageBox::Show("Выбранный водитель недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Создаем и добавляем поездку
        return tripList->InternalAddTrip(startPoint, finishPoint, price,
            bus, driver, depDate, depTime);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::RemoveTrip(String^ route) {
    try {
        return tripList->InternalRemoveTrip(route);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::EditTrip(String^ oldRoute, String^ newStartPoint, String^ newFinishPoint,
    int newPrice, String^ newBusCode, String^ newDriverFio,
    DateTime newDepDate, String^ newDepTime) {
    try {
        // TODO: Реализовать редактирование поездки
        // Пока используем удаление + добавление
        Trip^ trip = tripList->FindTripByRoute(oldRoute);
        if (trip == nullptr) {
            MessageBox::Show("Поездка не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Получаем текущие значения или новые
        String^ startPoint = String::IsNullOrEmpty(newStartPoint) ?
            trip->GetStartPoint() : newStartPoint;

        String^ finishPoint = String::IsNullOrEmpty(newFinishPoint) ?
            trip->GetFinishPoint() : newFinishPoint;

        int price = (newPrice > 0) ? newPrice : trip->GetPrice();

        Bus^ bus = trip->GetBus();
        if (!String::IsNullOrEmpty(newBusCode)) {
            Bus^ newBus = FindBus(newBusCode);
            if (newBus != nullptr) bus = newBus;
        }

        Driver^ driver = trip->GetDriver();
        if (!String::IsNullOrEmpty(newDriverFio)) {
            Driver^ newDriver = FindDriver(newDriverFio);
            if (newDriver != nullptr) driver = newDriver;
        }

        DateTime depDate = (newDepDate != DateTime::MinValue) ?
            newDepDate : trip->GetTripDate();

        String^ depTime = String::IsNullOrEmpty(newDepTime) ?
            trip->GetTripTime() : newDepTime;

        // Удаляем старую и добавляем новую
        RemoveTrip(oldRoute);
        return AddTrip(startPoint, finishPoint, price,
            bus->GetCode(), driver->GetFullName(),
            depDate, depTime);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при редактировании поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

Trip^ Admin::FindTrip(String^ route) {
    return tripList->FindTripByRoute(route);
}

bool Admin::StartTrip(String^ route) {
    try {
        Trip^ trip = FindTrip(route);
        if (trip == nullptr) {
            MessageBox::Show("Поездка не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        trip->StartTrip();
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при начале поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::CompleteTrip(String^ route) {
    try {
        Trip^ trip = FindTrip(route);
        if (trip == nullptr) {
            MessageBox::Show("Поездка не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        trip->CompleteTrip();
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при завершении поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool Admin::CancelTrip(String^ route) {
    try {
        Trip^ trip = FindTrip(route);
        if (trip == nullptr) {
            MessageBox::Show("Поездка не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        trip->CancelTrip();
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при отмене поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// === ПОЛУЧЕНИЕ ДАННЫХ ===

List<Driver^>^ Admin::GetAllDrivers() {
    return driversList->AllDrivers;
}

List<Bus^>^ Admin::GetAllBuses() {
    return busList->AllBuses;
}

List<Trip^>^ Admin::GetAllTrips() {
    return tripList->AllTrips;
}

List<Driver^>^ Admin::GetAvailableDrivers() {
    List<Driver^>^ result = gcnew List<Driver^>();
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetAvailability()) {
            result->Add(driver);
        }
    }
    return result;
}

List<Bus^>^ Admin::GetAvailableBuses() {
    return busList->GetAvailableBuses();
}

List<Trip^>^ Admin::GetPlannedTrips() {
    return tripList->GetPlannedTrips();
}

List<Trip^>^ Admin::GetActiveTrips() {
    return tripList->GetActiveTrips();
}

// === ФОРМЫ ===

void Admin::ShowDriversListForm(Form^ owner) {
    driversList->ShowDriversListForm(owner);
}

void Admin::ShowAddDriverForm(Form^ owner) {
    driversList->ShowAddDriverForm(owner);
}

void Admin::ShowDeleteDriverForm(Form^ owner) {
    driversList->ShowDeleteDriverForm(owner);
}

void Admin::ShowBusListForm(Form^ owner) {
    busList->ShowBusListForm(owner);
}

void Admin::ShowAddBusForm(Form^ owner) {
    busList->ShowAddBusForm(owner);
}

void Admin::ShowDeleteBusForm(Form^ owner) {
    busList->ShowDeleteBusForm(owner);
}

void Admin::ShowTripListForm(Form^ owner) {
    tripList->ShowTripListForm(owner, busList, driversList);
}

void Admin::ShowAddTripForm(Form^ owner) {
    tripList->ShowAddTripForm(owner, busList, driversList);
}

void Admin::ShowDeleteTripForm(Form^ owner) {
    tripList->ShowDeleteTripForm(owner);
}

void Admin::ShowEditTripForm(Form^ owner) {
    // TODO: Реализовать форму редактирования
    MessageBox::Show("Форма редактирования поездки в разработке", "Информация",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

// === СТАТИСТИКА ===

String^ Admin::GetSystemStatistics() {
    return String::Format(
        "=== СТАТИСТИКА СИСТЕМЫ ===\n"
        "Водителей: {0} (доступно: {1})\n"
        "Автобусов: {2} (доступно: {3})\n"
        "Поездок: {4} (активно: {5})\n"
        "===========================",
        GetTotalDrivers(), GetAvailableDriversCount(),
        GetTotalBuses(), GetAvailableBusesCount(),
        GetTotalTrips(), GetActiveTripsCount()
    );
}

int Admin::GetTotalDrivers() {
    return driversList->Count;
}

int Admin::GetTotalBuses() {
    return busList->Count;
}

int Admin::GetTotalTrips() {
    return tripList->Count;
}

int Admin::GetActiveTripsCount() {
    return tripList->ActiveCount;
}

int Admin::GetAvailableBusesCount() {
    return busList->AvailableCount;
}

int Admin::GetAvailableDriversCount() {
    int count = 0;
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetAvailability()) {
            count++;
        }
    }
    return count;
}