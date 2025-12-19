#include "User.hpp"
#include "Order.hpp"

using namespace InfSystBusStation;
using namespace System;

// Конструктор - вызывает конструктор People
User::User(String^ fullName, String^ gender, String^ passportSeries,
    String^ passportNumber, String^ email, String^ phone)
    : People(fullName, gender, passportSeries, passportNumber, email),  // Вызов конструктора People
    phoneNumber(phone),
    registrationDate(DateTime::Now),
    currentOrder(nullptr) {

    Console::WriteLine("[User] Создан: {0}", GetFullName());
}

User::~User() {
    // Order удаляется в форме, которая его создала
}

// Создание из формы
User^ User::CreateFromRegistrationForm(String^ fullName, String^ gender,
    String^ passportSeries, String^ passportNumber, String^ email, String^ phone) {

    return gcnew User(fullName, gender, passportSeries, passportNumber, email, phone);
}

// === РЕАЛИЗАЦИЯ АБСТРАКТНОГО МЕТОДА ===
double User::CalculateDiscount() {
    // Простая реализация - например, 10% скидка для зарегистрированных пользователей
    return 10.0;  // 10% скидка
}

// === ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ ===


String^ User::GetFullInfo() {
    // Расширяем базовую информацию
    String^ baseInfo = People::GetFullInfo();  // Базовая информация из People
    return baseInfo + String::Format(
        "\nТелефон: {0}\nДата регистрации: {1:dd.MM.yyyy}",
        phoneNumber, registrationDate
    );
}

// === НОВЫЕ МЕТОДЫ ===
bool User::ValidateUserData() {
    // Проверяем данные People + телефон
    if (String::IsNullOrEmpty(phoneNumber) || phoneNumber->Length < 10) {
        return false;
    }

    // Можно добавить базовую проверку
    if (String::IsNullOrEmpty(GetFullName()) || GetFullName()->Length < 5) {
        return false;
    }

    if (String::IsNullOrEmpty(GetEmail()) || !GetEmail()->Contains("@")) {
        return false;
    }

    return true;
}

String^ User::GetShortInfo() {
    return String::Format("{0} ({1})", GetFullName(), GetEmail());
}