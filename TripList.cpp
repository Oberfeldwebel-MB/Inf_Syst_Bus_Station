// TripList.cpp
#include "TripList.hpp"
#include "AddTripForm.h"
#include "DeleteTripForm.h"
#include "TimingForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор
TripList::TripList() {
    trips = gcnew List<Trip^>();
    stringData = gcnew Dictionary<String^, String^>();
    intData = gcnew Dictionary<String^, int>();
    doubleData = gcnew Dictionary<String^, double>();
}

// Деструктор
TripList::~TripList() {
    trips->Clear();
    stringData->Clear();
    intData->Clear();
    doubleData->Clear();
}

// === ОСНОВНЫЕ МЕТОДЫ УПРАВЛЕНИЯ ===

void TripList::AddTrip(Trip^ trip) {
    if (trip == nullptr) {
        throw gcnew ArgumentNullException("Нельзя добавить пустую ссылку на поездку!");
    }

    // Проверка на дублирование маршрута
    for each (Trip ^ existingTrip in trips) {
        if (existingTrip->GetRoute() == trip->GetRoute() &&
            !existingTrip->IsCompleted()) {
            throw gcnew InvalidOperationException(
                "Поездка с маршрутом '" + trip->GetRoute() + "' уже существует!");
        }
    }

    // Проверка доступности автобуса
    if (trip->GetBus() != nullptr && !trip->GetBus()->GetAvailability()) {
        throw gcnew InvalidOperationException("Автобус недоступен!");
    }

    // Проверка доступности водителя
    if (trip->GetDriver() != nullptr && !trip->GetDriver()->GetAvailability()) {
        throw gcnew InvalidOperationException("Водитель недоступен!");
    }

    trips->Add(trip);
    Console::WriteLine("[TripList] Поездка добавлена: {0}", trip->GetRoute());
}

bool TripList::RemoveTrip(String^ route) {
    String^ formattedRoute = route->Trim();

    for (int i = 0; i < trips->Count; i++) {
        if (trips[i]->GetRoute() == formattedRoute) {
            Trip^ trip = trips[i];

            // Освобождаем ресурсы
            if (trip->GetBus() != nullptr) {
                trip->GetBus()->ChangeAvailability(true);
            }

            // Удаляем поездку
            trips->RemoveAt(i);
            Console::WriteLine("[TripList] Поездка удалена: {0}", formattedRoute);
            return true;
        }
    }

    Console::WriteLine("[TripList] Поездка с маршрутом '{0}' не найдена", formattedRoute);
    return false;
}

Trip^ TripList::FindTripByRoute(String^ route) {
    String^ formattedRoute = route->Trim();

    for each (Trip ^ trip in trips) {
        if (trip->GetRoute() == formattedRoute) {
            return trip;
        }
    }
    return nullptr;
}

Trip^ TripList::ChooseTrip() {
    DisplayActiveTrips();

    if (trips->Count == 0) {
        MessageBox::Show("Нет доступных поездок!", "Информация",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return nullptr;
    }

    // TODO: Реализовать выбор поездки через форму
    return nullptr;
}

// === МЕТОДЫ ДЛЯ ФОРМ ===

bool TripList::ShowAddTripForm(Form^ owner, BusList^ busList, DriversList^ driverList) {
    try {
        AddTripForm^ form = gcnew AddTripForm();
        form->SetTripList(this);
        form->SetBusList(busList);
        form->SetDriverList(driverList);

        if (form->ShowDialog(owner) == DialogResult::OK) {
            return true;
        }
        return false;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы добавления поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool TripList::ShowDeleteTripForm(Form^ owner) {
    try {
        if (Count == 0) {
            MessageBox::Show("Расписание пусто!", "Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        DeleteTripForm^ form = gcnew DeleteTripForm(this);

        if (form->ShowDialog(owner) == DialogResult::OK) {
            return true;
        }
        return false;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы удаления поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

void TripList::ShowTripListForm(Form^ owner, BusList^ busList, DriversList^ driverList) {
    try {
        TimingForm^ form = gcnew TimingForm(this, busList, driverList, false);
        form->ShowDialog(owner);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии расписания: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// === ФИЛЬТРАЦИЯ И ПОИСК ===

List<Trip^>^ TripList::GetActiveTrips() {
    auto result = gcnew List<Trip^>();
    for each (Trip ^ trip in trips) {
        if (trip->IsPlanned() || trip->IsInProgress()) {
            result->Add(trip);
        }
    }
    return result;
}

List<Trip^>^ TripList::GetCompletedTrips() {
    auto result = gcnew List<Trip^>();
    for each (Trip ^ trip in trips) {
        if (trip->IsCompleted()) {
            result->Add(trip);
        }
    }
    return result;
}

List<Trip^>^ TripList::GetPlannedTrips() {
    auto result = gcnew List<Trip^>();
    for each (Trip ^ trip in trips) {
        if (trip->IsPlanned()) {
            result->Add(trip);
        }
    }
    return result;
}

List<Trip^>^ TripList::GetTripsByDate(DateTime date) {
    auto result = gcnew List<Trip^>();
    for each (Trip ^ trip in trips) {
        if (trip->GetTripDate().Date == date.Date) {
            result->Add(trip);
        }
    }
    return result;
}

List<Trip^>^ TripList::GetTripsByBus(String^ busCode) {
    auto result = gcnew List<Trip^>();
    String^ codeWithoutSlash = busCode->Replace("/", "");

    for each (Trip ^ trip in trips) {
        if (trip->GetBus() != nullptr &&
            trip->GetBus()->GetCode() == codeWithoutSlash) {
            result->Add(trip);
        }
    }
    return result;
}

List<Trip^>^ TripList::GetTripsByDriver(String^ driverName) {
    auto result = gcnew List<Trip^>();

    for each (Trip ^ trip in trips) {
        if (trip->GetDriver() != nullptr &&
            trip->GetDriver()->GetFullName() == driverName) {
            result->Add(trip);
        }
    }
    return result;
}

// === ОТОБРАЖЕНИЕ ===

void TripList::DisplayAllTrips() {
    Console::WriteLine("=== Все поездки ({0}) ===", Count);

    if (Count == 0) {
        Console::WriteLine("Расписание пусто");
    }
    else {
        int index = 1;
        for each (Trip ^ trip in trips) {
            Console::WriteLine("{0}. {1} [{2}] - {3} руб.",
                index++,
                trip->GetRoute(),
                trip->GetStatus(),
                trip->GetPrice());
        }
    }
    Console::WriteLine("==========================");
}

void TripList::DisplayActiveTrips() {
    auto activeTrips = GetActiveTrips();
    Console::WriteLine("=== Активные поездки ({0}) ===", activeTrips->Count);

    if (activeTrips->Count == 0) {
        Console::WriteLine("Нет активных поездок");
    }
    else {
        for each (Trip ^ trip in activeTrips) {
            Console::WriteLine("- {0} [{1}]", trip->GetRoute(), trip->GetStatus());
        }
    }
    Console::WriteLine("==========================");
}

void TripList::DisplayCompletedTrips() {
    auto completedTrips = GetCompletedTrips();
    Console::WriteLine("=== Завершенные поездки ({0}) ===", completedTrips->Count);

    if (completedTrips->Count == 0) {
        Console::WriteLine("Нет завершенных поездок");
    }
    else {
        for each (Trip ^ trip in completedTrips) {
            Console::WriteLine("- {0} - {1} руб.",
                trip->GetRoute(), trip->GetPrice());
        }
    }
    Console::WriteLine("==========================");
}

void TripList::DisplayPlannedTrips() {
    auto plannedTrips = GetPlannedTrips();
    Console::WriteLine("=== Запланированные поездки ({0}) ===", plannedTrips->Count);

    if (plannedTrips->Count == 0) {
        Console::WriteLine("Нет запланированных поездок");
    }
    else {
        for each (Trip ^ trip in plannedTrips) {
            Console::WriteLine("• {0} - {1} руб.",
                trip->GetRoute(), trip->GetPrice());
        }
    }
    Console::WriteLine("==========================");
}

// === ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ ===

void TripList::AddStringData(String^ key, String^ value) {
    stringData[key] = value;
}

void TripList::AddIntData(String^ key, int value) {
    intData[key] = value;
}

void TripList::AddDoubleData(String^ key, double value) {
    doubleData[key] = value;
}

String^ TripList::GetStringData(String^ key) {
    String^ value;
    if (stringData->TryGetValue(key, value)) {
        return value;
    }
    return String::Empty;
}

int TripList::GetIntData(String^ key) {
    int value;
    if (intData->TryGetValue(key, value)) {
        return value;
    }
    return 0;
}

double TripList::GetDoubleData(String^ key) {
    double value;
    if (doubleData->TryGetValue(key, value)) {
        return value;
    }
    return 0.0;
}

// === ВНУТРЕННИЕ МЕТОДЫ ДЛЯ ФОРМ ===

bool TripList::InternalAddTrip(String^ startPoint, String^ finishPoint, int price,
    Bus^ bus, Driver^ driver, DateTime date, String^ time) {
    try {
        // Проверка входных данных
        if (String::IsNullOrEmpty(startPoint)) {
            MessageBox::Show("Введите пункт отправления!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (String::IsNullOrEmpty(finishPoint)) {
            MessageBox::Show("Введите пункт назначения!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (price <= 0) {
            MessageBox::Show("Цена должна быть больше 0!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (bus == nullptr) {
            MessageBox::Show("Выберите автобус!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        if (driver == nullptr) {
            MessageBox::Show("Выберите водителя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Проверка доступности автобуса
        if (!bus->GetAvailability()) {
            MessageBox::Show("Выбранный автобус недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Проверка доступности водителя
        if (!driver->GetAvailability()) {
            MessageBox::Show("Выбранный водитель недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Создаем поездку
        Trip^ newTrip = gcnew Trip(startPoint, finishPoint, price, bus, driver, date, time);

        // Проверяем на дублирование маршрута
        String^ route = startPoint + " → " + finishPoint;
        if (FindTripByRoute(route) != nullptr) {
            MessageBox::Show("Поездка с таким маршрутом уже существует!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        // Добавляем поездку
        AddTrip(newTrip);
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

bool TripList::InternalRemoveTrip(String^ route) {
    return RemoveTrip(route);
}

List<String^>^ TripList::GetAllTripRoutes() {
    auto result = gcnew List<String^>();
    for each (Trip ^ trip in trips) {
        result->Add(trip->GetRoute());
    }
    return result;
}

Trip^ TripList::GetTripByRoute(String^ route) {
    return FindTripByRoute(route);
}



// Установить результаты поиска
void TripList::SetSearchResults(List<Trip^>^ results) {
    if (searchResults == nullptr) {
        searchResults = gcnew List<Trip^>();
    }
    searchResults->Clear();

    if (results != nullptr) {
        for each (Trip ^ trip in results) {
            searchResults->Add(trip);
        }
    }
}

// Получить результаты поиска
List<Trip^>^ TripList::GetSearchResults() {
    return searchResults;
}

// Очистить результаты поиска
void TripList::ClearSearchResults() {
    if (searchResults != nullptr) {
        searchResults->Clear();
    }
}

// Проверить наличие результатов
bool TripList::HasSearchResults() {
    return searchResults != nullptr && searchResults->Count > 0;
}