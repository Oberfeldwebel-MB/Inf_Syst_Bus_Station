#include "StartForm.h"
#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "Trip.hpp"
#include "Bus.hpp"
#include "Driver.hpp"
#include "Admin.hpp"

using namespace System;
using namespace System::Windows::Forms;
using namespace InfSystBusStation;

// Функция инициализации тестовых данных
void InitializeTestData(TripList^ tripList, BusList^ busList, DriversList^ driverList) {
    if (tripList == nullptr || busList == nullptr || driverList == nullptr) {
        return;
    }

    Console::WriteLine("[System] Инициализация тестовых данных...");

    // 1. Создаем тестовых водителей
    try {
        Driver^ driver1 = gcnew Driver(
            "И.И.Иванов", "Мужской",
            "1234", "567890", 50000, "B123456");

        Driver^ driver2 = gcnew Driver(
            "П.П.Петров", "Мужской",
            "2345", "678901", 55000, "C654321");

        Driver^ driver3 = gcnew Driver(
            "С.С.Сидорова", "Женский",
            "3456", "789012", 52000, "D789012");

        driverList->AddDriver(driver1);
        driverList->AddDriver(driver2);
        driverList->AddDriver(driver3);

        Console::WriteLine("[System] Добавлено {0} водителей", driverList->Count);
    }
    catch (Exception^ ex) {
        Console::WriteLine("[System] Ошибка при создании водителей: {0}", ex->Message);
    }

    // 2. Создаем тестовые автобусы
    try {
        Bus^ bus1 = gcnew Bus("01AA1234", "Mercedes", "Sprinter", "Отличное", 20);
        Bus^ bus2 = gcnew Bus("02BB5678", "Volvo", "9700", "Хорошее", 45);
        Bus^ bus3 = gcnew Bus("03CC9012", "MAN", "Lion's Coach", "Удовлетворительное", 50);

        busList->AddBus(bus1);
        busList->AddBus(bus2);
        busList->AddBus(bus3);

        Console::WriteLine("[System] Добавлено {0} автобусов", busList->Count);
    }
    catch (Exception^ ex) {
        Console::WriteLine("[System] Ошибка при создании автобусов: {0}", ex->Message);
    }

    // 3. Создаем тестовые поездки (если есть водители и автобусы)
    try {
        if (driverList->Count > 0 && busList->Count > 0) {
            List<Driver^>^ drivers = driverList->AllDrivers;
            List<Bus^>^ buses = busList->AllBuses;

            // Поездка 1: Москва - Санкт-Петербург
            Trip^ trip1 = gcnew Trip(
                "Москва", "Санкт-Петербург", 2500,
                buses[0], drivers[0],
                DateTime::Now.AddDays(1), "08:00");

            // Поездка 2: Санкт-Петербург - Москва  
            Trip^ trip2 = gcnew Trip(
                "Санкт-Петербург", "Москва", 2400,
                buses[1], drivers[1],
                DateTime::Now.AddDays(2), "10:30");

            // Поездка 3: Москва - Казань
            Trip^ trip3 = gcnew Trip(
                "Москва", "Казань", 1800,
                buses[2], drivers[2],
                DateTime::Now.AddDays(3), "14:15");

            tripList->AddTrip(trip1);
            tripList->AddTrip(trip2);
            tripList->AddTrip(trip3);

            Console::WriteLine("[System] Добавлено {0} поездок", tripList->Count);
        }
    }
    catch (Exception^ ex) {
        Console::WriteLine("[System] Ошибка при создании поездок: {0}", ex->Message);
    }

    Console::WriteLine("[System] Инициализация тестовых данных завершена");
}

// Основная точка входа приложения
[STAThread]
int main(array<String^>^ args) {
    try {
        Console::WriteLine("=== ЗАПУСК СИСТЕМЫ АВТОБУСНОГО ПАРКА ===");
        Console::WriteLine("Версия: 2.0");
        Console::WriteLine("Дата: {0}", DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss"));
        Console::WriteLine("=======================================");

        // Включаем визуальные стили Windows
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);

        // Создаем общие списки данных (единые для всей системы)
        Console::WriteLine("[System] Создание глобальных списков данных...");

        TripList^ globalTripList = gcnew TripList();
        BusList^ globalBusList = gcnew BusList();
        DriversList^ globalDriversList = gcnew DriversList();

        // Инициализируем тестовыми данными
        InitializeTestData(globalTripList, globalBusList, globalDriversList);

        Console::WriteLine("[System] Итоговые данные:");
        Console::WriteLine("  - Поездок: {0}", globalTripList->Count);
        Console::WriteLine("  - Автобусов: {0}", globalBusList->Count);
        Console::WriteLine("  - Водителей: {0}", globalDriversList->Count);

        // Создаем и запускаем стартовую форму с передачей списков
        Console::WriteLine("[System] Запуск стартовой формы...");
        StartForm^ startForm = gcnew StartForm(globalTripList, globalBusList, globalDriversList);

        // Запускаем главный цикл приложения
        Application::Run(startForm);

        Console::WriteLine("[System] Приложение завершено.");
        return 0;

    }
    catch (Exception^ ex) {
        // Критическая ошибка - показываем сообщение
        MessageBox::Show(
            String::Format(
                "Критическая ошибка при запуске приложения:\n\n{0}\n\n"
                "Пожалуйста, свяжитесь с технической поддержкой.",
                ex->Message
            ),
            "Фатальная ошибка",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );

        Console::WriteLine("[System] КРИТИЧЕСКАЯ ОШИБКА: {0}", ex->Message);
        Console::WriteLine("[System] Стек вызовов: {0}", ex->StackTrace);

        return 1;
    }
}