#include "User.hpp"
#include "Ticket.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор
User::User(String^ fioFormatted, String^ email, String^ phone)
    : People(fioFormatted, "Мужской", "1234", "567890", email),
    phoneNumber(phone),
    registrationDate(DateTime::Now),
    isRegistered(true),
    shoppingCart(nullptr) {

    // В реальной системе паспортные данные брать из формы
}

// Деструктор
User::~User() {
    if (shoppingCart != nullptr) {
        delete shoppingCart;
    }
}

// Создание User из формы регистрации
User^ User::CreateFromRegistrationForm(String^ fioFormatted,
    String^ email, String^ phone) {

    return gcnew User(fioFormatted, email, phone);
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
    if (shoppingCart == nullptr || shoppingCart->IsEmpty()) {
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
    return shoppingCart != nullptr && !shoppingCart->IsEmpty();
}

// === ИНФОРМАЦИЯ О КОРЗИНЕ ===

String^ User::GetCartSummary() {
    if (shoppingCart == nullptr || shoppingCart->IsEmpty()) {
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
    return String::Format(
        "Пользователь: {0}\n"
        "Email: {1}\n"
        "Телефон: {2}\n"
        "Дата регистрации: {3:dd.MM.yyyy}\n"
        "В корзине: {4} билетов",
        GetFullName(),
        GetEmail(),
        phoneNumber,
        registrationDate,
        GetCartTicketCount()
    );
}

double User::CalculateDiscount() {
    // Базовая скидка 5% для зарегистрированных пользователей
    return isRegistered ? 5.0 : 0.0;
}

// === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===

bool User::ValidateUserData() {
    if (String::IsNullOrEmpty(phoneNumber) || phoneNumber->Length < 10) {
        return false;
    }

    if (String::IsNullOrEmpty(GetEmail())) {
        return false;
    }

    return true;
}

String^ User::GetShortInfo() {
    return String::Format("{0} ({1})", GetFullName(), GetEmail());
}