// main.cpp
#include "StartForm.h"
#include "Admin.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "TripList.hpp"
#include "Order.hpp"

using namespace InfSystBusStation;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Создаем все объекты системы
    BusList^ busList = gcnew BusList();
    DriversList^ driversList = gcnew DriversList();
    TripList^ tripList = gcnew TripList();
    Order^ userOrder = gcnew Order();

    // Создаем Admin и передаем ему все списки
    Admin^ admin = gcnew Admin("admin123", "Иванов Иван Иванович",
        "4500", "123456", 50000, "admin@busstation.com");

    // Инициализируем систему (Admin сам создаст свои внутренние списки)
    admin->InitializeSystem();

    // Передаем ВСЕ объекты в StartForm
    StartForm^ startForm = gcnew StartForm(admin, busList, driversList, tripList);
    Application::Run(startForm);

    return 0;
}