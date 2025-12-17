#include "User.hpp"
#include "Ticket.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Основной конструктор со ВСЕМИ параметрами
User::User(String^ fioFormatted, String^ gender, String^ passportSeries,
    String^ passportNumber, String^ email, String^ phone)
    : People(fioFormatted, gender, passportSeries, passportNumber, email),
    phoneNumber(phone),
    registrationDate(DateTime::Now),
    isRegistered(true),
    shoppingCart(nullptr) {

    Console::WriteLine("[User] Создан новый пользователь: {0}", GetFullName());
}

// Деструктор
User::~User() {
    if (shoppingCart != nullptr) {
        delete shoppingCart;
    }
}

// Создание User из формы регистрации
User^ User::CreateFromRegistrationForm(String^ fioFormatted, String^ gender,
    String^ passportSeries, String^ passportNumber, String^ email, String^ phone) {

    return gcnew User(fioFormatted, gender, passportSeries, passportNumber, email, phone);
}

// === РАБОТА С КОРЗИНОЙ ===

void User::AddTicketToCart(Ticket^ ticket) {
    if (ticket == nullptr) return;

    ShoppingCart->AddTicket(ticket);
    Console::WriteLine("[User] {0} добавил билет (место №{1}) в корзину",
        GetFullName(), ticket->PlaceNumber);
}

void User::RemoveTicketFromCart(Ticket^ ticket) {
    if (shoppingCart != nullptr) {
        shoppingCart->RemoveTicket(ticket);
    }
}

void User::RemoveTicketFromCart(int placeNumber) {
    if (shoppingCart != nullptr) {
        shoppingCart->RemoveTicketByPlaceNumber(placeNumber);
    }
}

void User::ClearCart() {
    if (shoppingCart != nullptr) {
        shoppingCart->Clear();
    }
}

void User::CheckoutCart() {
    if (shoppingCart == nullptr || shoppingCart->IsEmpty) {
        throw gcnew InvalidOperationException("Корзина пуста!");
    }

    // Оплачиваем корзину
    shoppingCart->PayOrder();

    Console::WriteLine("[User] {0} оформил заказ #{1} на сумму {2:F2} руб.",
        GetFullName(), shoppingCart->OrderId, shoppingCart->TotalPrice);

    // После оформления можно очистить корзину или оставить для истории
    // ClearCart(); // Если нужно очистить после покупки
}

bool User::HasTicketsInCart() {
    return shoppingCart != nullptr && !shoppingCart->IsEmpty;
}

// === ИНФОРМАЦИЯ О КОРЗИНЕ ===

String^ User::GetCartSummary() {
    if (shoppingCart == nullptr || shoppingCart->IsEmpty) {
        return "Корзина пуста";
    }

    return String::Format(
        "Корзина ({0} билетов): {1:F2} руб.\n{2}",
        shoppingCart->TicketCount,
        shoppingCart->TotalPrice,
        shoppingCart->GetOrderSummary()
    );
}

int User::GetCartTicketCount() {
    return shoppingCart != nullptr ? shoppingCart->TicketCount : 0;
}

double User::GetCartTotalPrice() {
    return shoppingCart != nullptr ? shoppingCart->TotalPrice : 0.0;
}

List<Ticket^>^ User::GetCartTickets() {
    if (shoppingCart == nullptr) {
        return gcnew List<Ticket^>();
    }
    return shoppingCart->Tickets;
}

// === ВИРТУАЛЬНЫЕ МЕТОДЫ ===

void User::PrintInfo() {
    People::PrintInfo();
    Console::WriteLine("Телефон: {0}", phoneNumber);
    Console::WriteLine("Дата регистрации: {0:dd.MM.yyyy}", registrationDate);
    if (HasItemsInCart) {
        Console::WriteLine("В корзине: {0} билетов на {1:F2} руб.",
            GetCartTicketCount(), GetCartTotalPrice());
    }
}

String^ User::GetFullInfo() {
    String^ passportInfo = "";
    if (!String::IsNullOrEmpty(GetPassportSeries()) && !String::IsNullOrEmpty(GetPassportNumber())) {
        passportInfo = String::Format("\nПаспорт: {0} {1}", GetPassportSeries(), GetPassportNumber());
    }

    return String::Format(
        "Пользователь: {0}\n"
        "Email: {1}\n"
        "Телефон: {2}\n"
        "Дата регистрации: {3:dd.MM.yyyy}{4}",
        GetFullName(),
        GetEmail(),
        phoneNumber,
        registrationDate,
        passportInfo
    );
}

double User::CalculateDiscount() {
    // Базовая скидка 5% для зарегистрированных пользователей
    return isRegistered ? 5.0 : 0.0;
}

// === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===

bool User::ValidateUserData() {
    // Проверка телефона
    if (String::IsNullOrEmpty(phoneNumber) || phoneNumber->Length < 10) {
        Console::WriteLine("[User] Ошибка валидации: неверный номер телефона");
        return false;
    }

    // Проверка email
    if (String::IsNullOrEmpty(GetEmail()) || !GetEmail()->Contains("@")) {
        Console::WriteLine("[User] Ошибка валидации: неверный email");
        return false;
    }

    // Проверка ФИО
    if (String::IsNullOrEmpty(GetFullName()) || GetFullName()->Length < 5) {
        Console::WriteLine("[User] Ошибка валидации: неверное ФИО");
        return false;
    }

    Console::WriteLine("[User] Данные пользователя {0} прошли валидацию", GetFullName());
    return true;
}

String^ User::GetShortInfo() {
    return String::Format("{0} ({1})", GetFullName(), GetEmail());
}