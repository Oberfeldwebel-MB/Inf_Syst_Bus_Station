#include "Admin.hpp"
#include "Search.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

// Конструктор Admin (без значения по умолчанию)
Admin::Admin(String^ password, String^ fullName,
    String^ passportSeries, String^ passportNumber, int salary, String^ email)
    : Workers(fullName, "Мужской", passportSeries, passportNumber, salary, email) {

    adminPassword = password;
    hireDate = DateTime::Now;

    // Инициализируем подсистемы
    driversList = gcnew DriversList();
    busList = gcnew BusList();
    tripList = gcnew TripList();

    // Устанавливаем статус администратора
    SetStatus("Администратор системы");
}

// Деструктор
Admin::~Admin() {

}

// Инициализация системы
void Admin::InitializeSystem() {
    Console::WriteLine("[Admin] Система инициализирована администратором: " + GetFullName());
}

// Аутентификация через email
bool Admin::Authenticate(String^ email, String^ password) {
    return (email == GetEmail() && password == adminPassword);
}

// Смена пароля
void Admin::ChangePassword(String^ oldPassword, String^ newPassword) {
    // Используем email для проверки старого пароля
    if (Authenticate(GetEmail(), oldPassword)) {
        adminPassword = newPassword;
    }
    else {
        throw gcnew UnauthorizedAccessException("Неверный старый пароль или email!");
    }
}

// === ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ ===

void Admin::PrintInfo() {
    Workers::PrintInfo(); // Вызов метода базового класса
    Console::WriteLine("Должность: Администратор");
    Console::WriteLine("Email: {0}", GetEmail());
    Console::WriteLine("Дата найма: {0:dd.MM.yyyy}", hireDate);
}

String^ Admin::GetFullInfo() {
    return "Администратор: " + GetFullName() +
        " | Email: " + GetEmail() +
        " | Найм: " + hireDate.ToString("dd.MM.yyyy");
}

double Admin::CalculateDiscount() {
    return 0.2; // 20% скидка для администратора
}

// === ДЕЛЕГИРУЮЩИЕ МЕТОДЫ ===

void Admin::ShowBusManagementForm(Form^ owner) {
    if (!IsSystemInitialized) {
        MessageBox::Show("Система не инициализирована!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    busList->ShowBusListForm(owner);
}

void Admin::ShowDriverManagementForm(Form^ owner) {
    if (!IsSystemInitialized) {
        MessageBox::Show("Система не инициализирована!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    //driversList->ShowDriversListForm(owner);
}

void Admin::ShowTripManagementForm(Form^ owner) {
    if (!IsSystemInitialized) {
        MessageBox::Show("Система не инициализирована!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // Передаем все три параметра, так как TimingForm требует их
    tripList->ShowTripListForm(owner, busList, driversList);
}

List<Driver^>^ Admin::FindAvailableDrivers() {
    List<Driver^>^ result = gcnew List<Driver^>();
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetAvailability()) {
            result->Add(driver);
        }
    }
    return result;
}

// === СТАТИСТИКА ===

String^ Admin::GetSystemStatistics() {
    if (!IsSystemInitialized) {
        return "Система не инициализирована";
    }

    int driverCount = driversList->Count;
    int busCount = busList->Count;
    int tripCount = tripList->Count;

    int availableDrivers = 0;
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetAvailability()) availableDrivers++;
    }

    int availableBuses = busList->AvailableCount;
    int activeTrips = tripList->ActiveCount;

    return String::Format(
        "=== СТАТИСТИКА СИСТЕМЫ ===\n"
        "Администратор: {0}\n"
        "Email: {1}\n"
        "Дата найма: {2:dd.MM.yyyy}\n\n"
        "Водители: {3} (доступно: {4})\n"
        "Автобусы: {5} (доступно: {6})\n"
        "Поездки: {7} (активно: {8})\n"
        "===========================",
        GetFullName(),
        GetEmail(),
        hireDate,
        driverCount, availableDrivers,
        busCount, availableBuses,
        tripCount, activeTrips
    );
}

void Admin::GenerateReport(String^ reportType) {
    if (!IsSystemInitialized) {
        MessageBox::Show("Система не инициализирована!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    String^ report = "";
    String^ timestamp = DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss");
    String^ adminInfo = String::Format("Отчет сгенерирован: {0}\nАдминистратор: {1} ({2})\n\n",
        timestamp, GetFullName(), GetEmail());

    if (reportType == "drivers") {
        report = "=== ОТЧЕТ ПО ВОДИТЕЛЯМ ===\n" + adminInfo;
        for each (Driver ^ driver in driversList->AllDrivers) {
            report += String::Format("{0} - {1} руб. (Доступен: {2})\n",
                driver->GetFullName(), driver->GetSalary(),
                driver->GetAvailability() ? "Да" : "Нет");
        }
    }
    else if (reportType == "buses") {
        report = "=== ОТЧЕТ ПО АВТОБУСАМ ===\n" + adminInfo;
        for each (Bus ^ bus in busList->AllBuses) {
            report += String::Format("{0} - {1} (Состояние: {2}, Доступен: {3})\n",
                bus->GetFormattedCode(), bus->GetFullName(),
                bus->GetTechCondition(),
                bus->GetAvailability() ? "Да" : "Нет");
        }
    }
    else if (reportType == "trips") {
        report = "=== ОТЧЕТ ПО ПОЕЗДКАМ ===\n" + adminInfo;
        for each (Trip ^ trip in tripList->AllTrips) {
            report += String::Format("{0} - {1} руб. (Статус: {2})\n",
                trip->GetRoute(), trip->GetPrice());
                //trip->GetTripStatus());
        }
    }
    else if (reportType == "system") {
        report = GetSystemStatistics();
    }

    // Показываем отчет
    MessageBox::Show(report, "Отчет: " + reportType,
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}