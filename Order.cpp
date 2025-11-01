#include "Order.hpp"
#include "Search.hpp"

void Order::PrintOrderInfo() const {
    std::cout << "=== Информация о заказе ===\n";
    std::cout << "Статус оплаты: " << PayStatus << "\n";
    std::cout << "Общая стоимость: " << TotalPrice << " руб.\n";
    std::cout << "Количество билетов: " << TicketList.size() << "\n\n";

    for (const auto& ticket : TicketList) {
        ticket.PrintTicketInfo();
        std::cout << "\n";
    }
    std::cout << "===========================\n";
}

void Order::CalculateTotalPrice() {
    TotalPrice = 0;
    for (const auto& ticket : TicketList) {
        TotalPrice += ticket.GetFinalPrice();
    }
}

void Order::AddTicket(const Ticket& ticket) {
    //Проверяем, нет ли уже билета с таким номером места в заказе
    for (const auto& existing_ticket : TicketList) {
        if (existing_ticket.GetPlaceNumber() == ticket.GetPlaceNumber()) {
            std::cout << "Ошибка: Билет на место " << ticket.GetPlaceNumber()
                << " уже есть в заказе!\n";
            return;
        }
    }

    // Проверяем, что билет доступен для добавления
    if (!ticket.IsAvailable()) {
        std::cout << "Ошибка: Билет на место " << ticket.GetPlaceNumber()
            << " недоступен для добавления!\n";
        return;
    }

    // Добавляем билет в заказ
    TicketList.push_back(ticket);

    // Пересчитываем общую стоимость
    CalculateTotalPrice();

    // Выводим информацию о добавлении
    std::cout << " Билет успешно добавлен в заказ:\n";
    std::cout << "   Место: " << ticket.GetPlaceNumber() << "\n";
    std::cout << "   Пассажир: " << ticket.GetPassenger().GetFullName() << "\n";
    std::cout << "   Маршрут: " << ticket.GetTrip().GetRoute() << "\n";
    std::cout << "   Тип: " << ticket.GetTicketTypeName() << "\n";
    std::cout << "   Цена: " << ticket.GetFinalPrice() << " руб.\n";
    std::cout << "   Статус: " << ticket.GetStatus() << "\n";
    std::cout << "   Всего билетов в заказе: " << TicketList.size() << "\n";
    std::cout << "   Общая стоимость заказа: " << TotalPrice << " руб.\n";
}

bool Order::RemoveTicket(const Ticket& ticket) {
    std::vector<Ticket*> foundtickets = search->SearchTickets(*this,
        ticket.GetPassenger().GetFullName(),  // Имя пассажира
        ticket.GetTrip().GetRoute(),          // Маршрут
        ticket.GetPlaceNumber(),
        ticket.GetTicketType()           // Тип билета
    );

    for (Ticket* foundticket : foundtickets) {
        if (foundticket->GetPlaceNumber() == ticket.GetPlaceNumber()) {
            int seatnumber = foundticket->GetPlaceNumber();

            // Возвращаем место в автобус
            if (ticketchose != nullptr) {
                ticketchose->ReleaseSeat(seatnumber);
            }

            // Удаляем билет из заказа
            for (auto it = TicketList.begin(); it != TicketList.end(); ++it) {
                if (it->GetPlaceNumber() == seatnumber) {
                    TicketList.erase(it);
                    CalculateTotalPrice();

                    std::cout << "Билет удален из заказа\n";
                    std::cout << "Место: " << seatnumber << "\n";
                    std::cout << "Пассажир: " << ticket.GetPassenger().GetFullName() << "\n";
                    std::cout << "Место " << seatnumber << " снова доступно для бронирования\n";
                    return true;
                }
            }
        }
    }

    std::cout << "Билет не найден в заказе!\n";
    std::cout << "Место: " << ticket.GetPlaceNumber() << "\n";
    std::cout << "Пассажир: " << ticket.GetPassenger().GetFullName() << "\n";
    return false;
}

