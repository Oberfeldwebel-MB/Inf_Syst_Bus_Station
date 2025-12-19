#include "Order.hpp"
#include "User.hpp"    // Добавляем для доступа к User

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструкторы (без изменений)
Order::Order() {
    tickets = gcnew List<Ticket^>();
    orderId = GenerateOrderId();
    status = "Создан";
    totalPrice = 0.0;
    orderDate = DateTime::Now;
    passengerName = "Не указан";
}

Order::Order(String^ passengerName) : Order() {
    this->passengerName = passengerName;
}

Order::Order(String^ orderId, String^ passengerName) : Order(passengerName) {
    this->orderId = orderId;
}

// Деструктор (без изменений)
Order::~Order() {
    tickets = nullptr;
}

// === ОСНОВНЫЕ МЕТОДЫ УПРАВЛЕНИЯ БИЛЕТАМИ ===

void Order::AddTicket(Ticket^ ticket) {
    if (ticket == nullptr) {
        throw gcnew ArgumentNullException("Нельзя добавить пустой билет!");
    }

    // Проверка на дублирование места
    for each (Ticket ^ existingTicket in tickets) {
        if (existingTicket->PlaceNumber == ticket->PlaceNumber) {
            throw gcnew InvalidOperationException(
                "Билет с местом №" + ticket->PlaceNumber + " уже есть в заказе!");
        }
    }

    tickets->Add(ticket);
    CalculateTotalPrice();

    // Обновляем имя пассажира в заказе, если не указано
    if (ticket->PassengerData != nullptr && passengerName == "Не указан") {
        passengerName = ticket->PassengerData->GetFullName();
    }

    Console::WriteLine("[Order] Билет добавлен в заказ {0}: место №{1}", orderId, ticket->PlaceNumber);
}

bool Order::RemoveTicket(Ticket^ ticket) {
    if (ticket == nullptr) return false;

    bool removed = tickets->Remove(ticket);
    if (removed) {
        CalculateTotalPrice();
        Console::WriteLine("[Order] Билет удален из заказа {0}: место №{1}", orderId, ticket->PlaceNumber);
    }
    return removed;
}

bool Order::RemoveTicketByIndex(int index) {
    if (index < 0 || index >= tickets->Count) {
        return false;
    }

    Ticket^ ticket = tickets[index];
    tickets->RemoveAt(index);
    CalculateTotalPrice();
    Console::WriteLine("[Order] Билет удален из заказа {0}: место №{1}", orderId, ticket->PlaceNumber);
    return true;
}

bool Order::RemoveTicketByPlaceNumber(int placeNumber) {
    for (int i = 0; i < tickets->Count; i++) {
        if (tickets[i]->PlaceNumber == placeNumber) {
            tickets->RemoveAt(i);
            CalculateTotalPrice();
            Console::WriteLine("[Order] Билет удален из заказа {0}: место №{1}", orderId, placeNumber);
            return true;
        }
    }
    return false;
}

void Order::Clear() {
    tickets->Clear();
    totalPrice = 0.0;
    status = "Отменен";
    passengerName = "Не указан";
    Console::WriteLine("[Order] Заказ {0} очищен", orderId);
}

// === ПОИСК БИЛЕТОВ В ЗАКАЗЕ ===

Ticket^ Order::FindTicketByPlaceNumber(int placeNumber) {
    for each (Ticket ^ ticket in tickets) {
        if (ticket->PlaceNumber == placeNumber) {
            return ticket;
        }
    }
    return nullptr;
}

Ticket^ Order::FindTicketByPassenger(String^ passengerName) {
    for each (Ticket ^ ticket in tickets) {
        if (ticket->PassengerData != nullptr) {
            // Теперь PassengerData - это User^, поэтому используем GetFullName()
            String^ fullName = ticket->PassengerData->GetFullName();
            if (fullName == passengerName) {
                return ticket;
            }
        }
    }
    return nullptr;
}

List<Ticket^>^ Order::FindTicketsByType(TicketType type) {
    auto result = gcnew List<Ticket^>();
    for each (Ticket ^ ticket in tickets) {
        if (ticket->Type == type) {
            result->Add(ticket);
        }
    }
    return result;
}

// === ОПЕРАЦИИ С ЗАКАЗОМ ===

bool Order::PayOrder() {
    try {
        if (status == "Оплачен") {
            throw gcnew InvalidOperationException("Заказ уже оплачен!");
        }

        if (tickets->Count == 0) {
            throw gcnew InvalidOperationException("Нельзя оплатить пустой заказ!");
        }

        // Помечаем все билеты как оплаченные
        for each (Ticket ^ ticket in tickets) {
            ticket->MarkAsPaid();
        }

        status = "Оплачен";
        Console::WriteLine("[Order] Заказ {0} оплачен. Сумма: {1:F2} руб.", orderId, totalPrice);
        return true;
    }
    catch (Exception^ ex) {
        Console::WriteLine("[Order] Ошибка при оплате заказа {0}: {1}", orderId, ex->Message);
        return false;
    }
}

void Order::CancelOrder() {
    status = "Отменен";
    Console::WriteLine("[Order] Заказ {0} отменен", orderId);
}

void Order::CalculateTotalPrice() {
    totalPrice = 0.0;
    for each (Ticket ^ ticket in tickets) {
        totalPrice += ticket->FinalPrice;
    }
}

bool Order::ApplyDiscount(double discountPercent) {
    try {
        if (discountPercent < 0 || discountPercent > 100) {
            throw gcnew ArgumentException("Скидка должна быть в диапазоне 0-100%");
        }

        if (status == "Оплачен") {
            throw gcnew InvalidOperationException("Нельзя применить скидку к оплаченному заказу!");
        }

        double discountMultiplier = 1.0 - (discountPercent / 100.0);

        // Применяем скидку ко всем билетам
        for each (Ticket ^ ticket in tickets) {
            ticket->FinalPrice = ticket->FinalPrice * discountMultiplier;
        }

        CalculateTotalPrice();
        Console::WriteLine("[Order] К заказу {0} применена скидка {1:F0}%", orderId, discountPercent);
        return true;
    }
    catch (Exception^ ex) {
        Console::WriteLine("[Order] Ошибка при применении скидки: {0}", ex->Message);
        return false;
    }
}

// === ПРОВЕРКИ ===

bool Order::CanBePaid() {
    return status == "Создан" && tickets->Count > 0;
}

bool Order::HasTickets() {
    return tickets->Count > 0;
}

// === ОТОБРАЖЕНИЕ ===

void Order::PrintOrderInfo() {
    Console::WriteLine("=== ИНФОРМАЦИЯ О ЗАКАЗЕ ===");
    Console::WriteLine("ID заказа: {0}", orderId);
    Console::WriteLine("Пассажир: {0}", passengerName);
    Console::WriteLine("Дата: {0}", orderDate.ToString("dd.MM.yyyy HH:mm"));
    Console::WriteLine("Статус: {0}", status);
    Console::WriteLine("Количество билетов: {0}", tickets->Count);
    Console::WriteLine("Общая сумма: {0:F2} руб.", totalPrice);

    // Выводим информацию о пассажирах
    if (tickets->Count > 0 && tickets[0]->PassengerData != nullptr) {
        Console::WriteLine("Данные пассажира:");
        User^ user = tickets[0]->PassengerData;
        Console::WriteLine("  ФИО: {0}", user->GetFullName());
        Console::WriteLine("  Email: {0}", user->GetEmail());
        Console::WriteLine("  Телефон: {0}", user->PhoneNumber);
    }

    Console::WriteLine("===========================");
}

String^ Order::GetOrderSummary() {
    String^ summary = String::Format(
        "Заказ #{0}\n"
        "Пассажир: {1}\n"
        "Дата: {2}\n"
        "Статус: {3}\n"
        "Билетов: {4}\n"
        "Сумма: {5:F2} руб.\n"
        "================\n",
        orderId,
        passengerName,
        orderDate.ToString("dd.MM.yyyy HH:mm"),
        status,
        tickets->Count,
        totalPrice
    );

    int index = 1;
    for each (Ticket ^ ticket in tickets) {
        String^ passengerInfo = "Не указан";
        if (ticket->PassengerData != nullptr) {
            passengerInfo = ticket->PassengerData->GetFullName();
        }

        summary += String::Format("{0}. Место №{1}: {2} ({3}) - {4:F2} руб.\n",
            index++,
            ticket->PlaceNumber,
            ticket->TicketTypeName,
            passengerInfo,
            ticket->FinalPrice
        );
    }

    return summary;
}

String^ Order::GetReceipt() {
    String^ receipt = "================================\n";
    receipt += "          КВИТАНЦИЯ ОБ ОПЛАТЕ\n";
    receipt += "================================\n";
    receipt += String::Format("Номер заказа: {0}\n", orderId);
    receipt += String::Format("Пассажир: {0}\n", passengerName);
    receipt += String::Format("Дата: {0}\n", orderDate.ToString("dd.MM.yyyy HH:mm:ss"));
    receipt += "--------------------------------\n";

    int itemNumber = 1;
    for each (Ticket ^ ticket in tickets) {
        String^ passengerInfo = "";
        if (ticket->PassengerData != nullptr) {
            passengerInfo = String::Format(" ({0})", ticket->PassengerData->GetFullName());
        }

        receipt += String::Format("{0}. Билет {1} (место {2}){3}: {4:F2} руб.\n",
            itemNumber++,
            ticket->TicketTypeName,
            ticket->PlaceNumber,
            passengerInfo,
            ticket->FinalPrice
        );
    }

    receipt += "--------------------------------\n";
    receipt += String::Format("ИТОГО К ОПЛАТЕ: {0:F2} руб.\n", totalPrice);
    receipt += "================================\n";
    receipt += "        СПАСИБО ЗА ПОКУПКУ!\n";
    receipt += "================================\n";

    return receipt;
}

void Order::DisplayTickets() {
    Console::WriteLine("=== Билеты в заказе {0} ===", orderId);

    if (tickets->Count == 0) {
        Console::WriteLine("Нет билетов");
    }
    else {
        int index = 1;
        for each (Ticket ^ ticket in tickets) {
            String^ passengerInfo = "Не указан";
            if (ticket->PassengerData != nullptr) {
                passengerInfo = ticket->PassengerData->GetFullName();
            }

            Console::WriteLine("{0}. Место №{1}: {2} - {3:F2} руб. ({4}) [Пассажир: {5}]",
                index++,
                ticket->PlaceNumber,
                ticket->TicketTypeName,
                ticket->FinalPrice,
                ticket->Status,
                passengerInfo
            );
        }
    }
    Console::WriteLine("==========================");
}

// === СТАТИСТИКА ПО ЗАКАЗУ ===

int Order::GetTicketCountByType(TicketType type) {
    int count = 0;
    for each (Ticket ^ ticket in tickets) {
        if (ticket->Type == type) {
            count++;
        }
    }
    return count;
}

double Order::GetTotalPriceByType(TicketType type) {
    double total = 0.0;
    for each (Ticket ^ ticket in tickets) {
        if (ticket->Type == type) {
            total += ticket->FinalPrice;
        }
    }
    return total;
}

Dictionary<TicketType, int>^ Order::GetTicketsStatistics() {
    auto stats = gcnew Dictionary<TicketType, int>();

    // Инициализируем для всех типов
    stats->Add(TicketType::ADULT, 0);
    stats->Add(TicketType::CHILD, 0);
    stats->Add(TicketType::LUGGAGE, 0);

    // Считаем
    for each (Ticket ^ ticket in tickets) {
        stats[ticket->Type] = stats[ticket->Type] + 1;
    }

    return stats;
}

// === ОПЕРАТОРЫ ===

Order^ Order::operator+(Order^ order, Ticket^ ticket) {
    if (order == nullptr) {
        order = gcnew Order();
    }

    order->AddTicket(ticket);
    return order;
}

Order^ Order::operator-(Order^ order, Ticket^ ticket) {
    if (order != nullptr) {
        order->RemoveTicket(ticket);
    }
    return order;
}

// === СТАТИЧЕСКИЕ МЕТОДЫ ===

String^ Order::GenerateOrderId() {
    Random^ random = gcnew Random();
    int randomNum = random->Next(1000, 9999);
    return String::Format("ORD-{0}-{1}",
        DateTime::Now.ToString("yyyyMMdd"),
        randomNum);
}