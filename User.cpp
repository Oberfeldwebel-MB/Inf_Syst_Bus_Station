#include "User.hpp"
#include <iostream>

using namespace InfSystBusStation;
using namespace System;
using namespace System::Text::RegularExpressions;

// Основной конструктор (БЕЗ Timing!)
User::User(String^ fullName, String^ gender,
    String^ passportSeries, String^ passportNumber,
    String^ email, String^ phone)
    : People(fullName, gender, passportSeries, passportNumber, email)
{
    phoneNumber = phone;
    userOrder = nullptr;
    registrationDate = DateTime::Now;
}

// Конструктор для формы (раздельное ФИО)
User::User(String^ surname, String^ name, String^ patronymic,
    String^ gender, String^ passportSeries, String^ passportNumber,
    String^ email, String^ phone)
    : People(surname + " " + name + " " + patronymic,
        gender, passportSeries, passportNumber, email)
{
    phoneNumber = phone;
    userOrder = nullptr;
    registrationDate = DateTime::Now;
}

// Деструктор
User::~User() {
    // Управляемые ресурсы очищаются автоматически
}

// Создание User из данных формы
User^ User::CreateFromFormData(String^ fio, String^ gender,
    String^ passportSeries, String^ passportNumber,
    String^ email, String^ phone)
{
    // ... реализация ...
}

// Методы для работы с заказом (ПРОСТЫЕ ЗАГЛУШКИ)
void User::CreateOrder(/* параметры */) {
    // Заказ должен создаваться через отдельный сервис/форму
    // а не храниться в User
    Console::WriteLine("[User] Создание заказа...");
    // userOrder = gcnew Order(...);
}

void User::ViewMyOrder() {
    if (userOrder == nullptr || userOrder->IsEmpty()) {
        Console::WriteLine("[User] Нет активных заказов");
        return;
    }
    userOrder->PrintOrderInfo();
}

void User::CancelOrder() {
    if (userOrder != nullptr) {
        userOrder->CancelOrder();
        userOrder = nullptr;
        Console::WriteLine("[User] Заказ отменен");
    }
}

// ... остальные методы без изменений ...