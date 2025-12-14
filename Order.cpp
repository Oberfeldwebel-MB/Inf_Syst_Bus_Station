#include "Order.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// === РЕАЛИЗАЦИЯ КОНСТРУКТОРОВ ===

// Основной конструктор
Order::Order(TicketChose^ chose) {
    if (chose == nullptr) {
        throw gcnew ArgumentNullException("TicketChose не может быть null");
    }

    ticketchose = chose;
    ticketList = gcnew List<Ticket^>();
    payStatus = "Не оплачен";
    totalPrice = 0.0;
    orderId = GenerateOrderId();
    orderDate = DateTime::Now;
    search = nullptr;

    Console::WriteLine("[Order] Создан новый заказ: " + orderId);
}

// Конструктор с ID
Order::Order(TicketChose^ chose, String^ id) {
    if (chose == nullptr) {
        throw gcnew ArgumentNullException("TicketChose не может быть null");
    }

    if (String::IsNullOrEmpty(id)) {
        throw gcnew ArgumentException("ID заказа не может быть пустым");
    }

    ticketchose = chose;
    ticketList = gcnew List<Ticket^>();
    payStatus = "Не оплачен";
    totalPrice = 0.0;
    orderId = id;
    orderDate = DateTime::Now;
    search = nullptr;
}

// Конструктор копирования
Order::Order(Order^ other) {
    if (other == nullptr) {
        throw gcnew ArgumentNullException("Копируемый Order не может быть null");
    }

    // Копируем простые поля
    payStatus = other->payStatus;
    totalPrice = other->totalPrice;
    orderId = other->orderId + "_copy";
    orderDate = DateTime::Now;

    // Копируем ссылки (поверхностное копирование)
    ticketchose = other->ticketchose;
    search = other->search;

    // Глубокое копирование списка билетов
    ticketList = gcnew List<Ticket^>();
    for each (Ticket ^ ticket in other->ticketList) {
        // Предполагаем, что Ticket имеет конструктор копирования
        Ticket^ newTicket = gcnew Ticket(ticket);
        ticketList->Add(newTicket);
    }
}

// Деструктор
Order::~Order() {
    // Управляемые ресурсы очищаются автоматически
    // Можно добавить логирование
    // Console::WriteLine("[Order] Деструктор: " + orderId);
}

// === ОСНОВНЫЕ МЕТОДЫ ===

void Order::PrintOrderInfo() {
    Console::WriteLine("=== ИНФОРМАЦИЯ О ЗАКАЗЕ ===");
    Console::WriteLine("ID заказа: " + orderId);
    Console::WriteLine("Дата: " + orderDate.ToString("dd.MM.yyyy HH:mm"));
    Console::WriteLine("Статус оплаты: " + payStatus);
    Console::WriteLine("Количество билетов: " + ticketList->Count);
    Console::WriteLine("Общая стоимость: " + totalPrice.ToString("F2") + " руб.");

    if (ticketList->Count > 0) {
        Console::WriteLine("\n=== БИЛЕТЫ ===");
        for (int i = 0; i < ticketList->Count; i++) {
            Console::Write((i + 1) + ". ");
            ticketList[i]->PrintInfo();  // Предполагаем, что Ticket имеет PrintInfo()
        }
    }

    Console::WriteLine("========================");
}

void Order::AddTicket(Ticket^ ticket) {
    if (ticket == nullptr) {
        throw gcnew ArgumentNullException("Билет не может быть null");
    }

    // Проверяем, не добавлен ли уже такой билет
    if (ContainsTicket(ticket)) {
        throw gcnew InvalidOperationException("Билет уже добавлен в заказ");
    }

    // Проверяем статус заказа
    if (payStatus == "Оплачен") {
        throw gcnew InvalidOperationException("Нельзя добавлять билеты в оплаченный заказ");
    }

    // Проверяем статус заказа
    if (payStatus == "Отменен") {
        throw gcnew InvalidOperationException("Нельзя добавлять билеты в отмененный заказ");
    }

    ticketList->Add(ticket);
    CalculateTotalPrice();

    Console::WriteLine("[Order] Добавлен билет в заказ " + orderId);
}

bool Order::RemoveTicket(Ticket^ ticket) {
    if (ticket == nullptr) {
        return false;
    }

    // Проверяем статус заказа
    if (payStatus == "Оплачен") {
        throw gcnew InvalidOperationException("Нельзя удалять билеты из оплаченного заказа");
    }

    bool removed = ticketList->Remove(ticket);

    if (removed) {
        CalculateTotalPrice();
        Console::WriteLine("[Order] Удален билет из заказа " + orderId);
    }

    return removed;
}

void Order::PayOrder() {
    if (ticketList->Count == 0) {
        throw gcnew InvalidOperationException("Нельзя оплатить пустой заказ");
    }

    if (payStatus == "Оплачен") {
        throw gcnew InvalidOperationException("Заказ уже оплачен");
    }

    if (payStatus == "Отменен") {
        throw gcnew InvalidOperationException("Нельзя оплатить отмененный заказ");
    }

    // Здесь может быть логика связи с платежной системой
    payStatus = "Оплачен";

    Console::WriteLine("[Order] Заказ " + orderId + " оплачен");
    Console::WriteLine("Сумма: " + totalPrice.ToString("F2") + " руб.");
}

void Order::CancelOrder() {
    if (payStatus == "Оплачен") {
        // Здесь может быть логика возврата денег
        Console::WriteLine("[Order] Внимание! Отмена оплаченного заказа " + orderId);
    }

    payStatus = "Отменен";

    Console::WriteLine("[Order] Заказ " + orderId + " отменен");
}

void Order::CalculateTotalPrice() {
    totalPrice = 0.0;

    for each (Ticket ^ ticket in ticketList) {
        totalPrice += ticket->GetPrice();  // Предполагаем, что Ticket имеет GetPrice()
    }

    // Применяем скидку если есть
    double discount = CalculateDiscount();
    if (discount > 0) {
        totalPrice *= (1.0 - discount);
    }
}

void Order::ClearOrder() {
    if (payStatus == "Оплачен") {
        throw gcnew InvalidOperationException("Нельзя очистить оплаченный заказ");
    }

    ticketList->Clear();
    totalPrice = 0.0;
    payStatus = "Не оплачен";

    Console::WriteLine("[Order] Заказ " + orderId + " очищен");
}

// === ПЕРЕГРУЗКА ОПЕРАТОРОВ ===

Order^ Order::operator+(Order^ order, Ticket^ ticket) {
    if (order == nullptr) {
        throw gcnew ArgumentNullException("Order не может быть null");
    }

    order->AddTicket(ticket);
    return order;
}

// === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===

String^ Order::GetOrderSummary() {
    String^ summary = String::Format(
        "Заказ #{0}\n"
        "Дата: {1:dd.MM.yyyy HH:mm}\n"
        "Статус: {2}\n"
        "Билетов: {3}\n"
        "Сумма: {4:F2} руб.",
        orderId, orderDate, payStatus, ticketList->Count, totalPrice);

    return summary;
}

bool Order::ContainsTicket(Ticket^ ticket) {
    if (ticket == nullptr) {
        return false;
    }

    for each (Ticket ^ t in ticketList) {
        // Предполагаем, что Ticket имеет метод сравнения
        if (t->Equals(ticket)) {
            return true;
        }
    }

    return false;
}

double Order::CalculateDiscount() {
    // Базовая скидка: 0% 
    double discount = 0.0;

    // Можно добавить логику скидок:
    // - за количество билетов
    // - за тип пользователя
    // - сезонные скидки и т.д.

    // Пример: скидка 5% за 3 и более билетов
    if (ticketList->Count >= 3) {
        discount = 0.05;
    }

    return discount;
}

void Order::ApplyDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 1) {
        throw gcnew ArgumentException("Скидка должна быть в диапазоне 0-1");
    }

    // Пересчитываем цену с учетом дополнительной скидки
    totalPrice *= (1.0 - discountPercent);
    Console::WriteLine("[Order] Применена скидка: " + (discountPercent * 100) + "%");
}

// === СТАТИЧЕСКИЕ МЕТОДЫ ===

String^ Order::GenerateOrderId() {
    // Генерация уникального ID заказа
    DateTime now = DateTime::Now;
    String^ timestamp = now.ToString("yyyyMMddHHmmss");
    Random^ rnd = gcnew Random();
    int randomNum = rnd->Next(1000, 9999);

    return "ORD-" + timestamp + "-" + randomNum;
}

String^ Order::GenerateReceipt(Order^ order) {
    if (order == nullptr) {
        throw gcnew ArgumentNullException("Order не может быть null");
    }

    if (order->payStatus != "Оплачен") {
        throw gcnew InvalidOperationException("Чек можно сгенерировать только для оплаченного заказа");
    }

    // Создаем строку чека
    System::Text::StringBuilder^ receipt = gcnew System::Text::StringBuilder();

    receipt->AppendLine("=== АВТОБУСНЫЙ ПАРК ===");
    receipt->AppendLine("         ЧЕК ОПЛАТЫ");
    receipt->AppendLine("=========================");
    receipt->AppendLine("Номер заказа: " + order->orderId);
    receipt->AppendLine("Дата: " + DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss"));
    receipt->AppendLine("=========================");

    for (int i = 0; i < order->ticketList->Count; i++) {
        receipt->AppendLine(String::Format("{0}. {1}",
            i + 1,
            order->ticketList[i]->GetDescription()));  // Предполагаем GetDescription()
    }

    receipt->AppendLine("=========================");
    receipt->AppendLine("Количество: " + order->ticketList->Count);
    receipt->AppendLine("Итого: " + order->totalPrice.ToString("F2") + " руб.");
    receipt->AppendLine("Статус: " + order->payStatus);
    receipt->AppendLine("=========================");
    receipt->AppendLine("Спасибо за покупку!");

    return receipt->ToString();
}