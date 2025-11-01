#include "User.hpp"
#include "Timing.hpp"
#include "TicketChose.hpp"
#include "Trip.hpp"
#include "Passenger.hpp"
#include <iostream>

User::User(const std::string& surname,
    const std::string& name,
    const std::string& fatName,
    const std::string& psprtSer,
    const std::string& psprtNum,
    const std::string& email,
    Timing* timingPtr)
    : People(surname, name, fatName, psprtSer, psprtNum, email),
    userOrder(nullptr), timing(timingPtr) {
}



void User::InitializeOrder(TicketChose* ticketChose) {
    if (userOrder) {
        delete userOrder;  // Удаление старого заказа
    }
    userOrder = new Order(ticketChose);  //новый заказ
}

void User::SearchAndBookTicket() {
    if (!timing) {
        std::cout << "Ошибка: расписание не доступно!\n";
        return;
    }

    std::cout << "=== ПОИСК И БРОНИРОВАНИЕ БИЛЕТА ===\n";

    // 1. Поиск поездок
    std::string start, finish;
    std::cout << "Введите пункт отправления: ";
    std::getline(std::cin, start);
    std::cout << "Введите пункт назначения: ";
    std::getline(std::cin, finish);

    // Ищем поездки по маршруту
    std::vector<Trip*> foundTrips = search.SearchTripsByRoute(*timing, start, finish);

    if (foundTrips.empty()) {
        std::cout << "Поездки по маршруту " << start << " - " << finish << " не найдены!\n";
        return;
    }

    // 2. Показываем найденные поездки
    std::cout << "\n=== НАЙДЕННЫЕ ПОЕЗДКИ ===\n";
    for (size_t i = 0; i < foundTrips.size(); ++i) {
        std::cout << i + 1 << ". ";
        foundTrips[i]->Print_trip_info();
    }

    // 3. Выбор поездки
    int tripChoice;
    std::cout << "Выберите поездку (1-" << foundTrips.size() << "): ";
    std::cin >> tripChoice;
    std::cin.ignore();

    if (tripChoice < 1 || tripChoice > foundTrips.size()) {
        std::cout << "Неверный выбор!\n";
        return;
    }

    Trip* selectedTrip = foundTrips[tripChoice - 1];

    // 4.TicketChose для выбранной поездки
    TicketChose ticketChooser(*selectedTrip);

    // Инициализация заказа
    if (!userOrder) {
        InitializeOrder(&ticketChooser);
    }

    // 6. Показываем доступные места
    ticketChooser.ShowAvailableSeats();

    // 7. Выбор места
    int seatNumber;
    std::cout << "Выберите номер места: ";
    std::cin >> seatNumber;
    std::cin.ignore();

    // Выбор типа билета
    std::cout << "Выберите тип билета:\n";
    std::cout << "0 - Взрослый\n1 - Детский\n2 - Багажный\n";
    int ticketTypeChoice;
    std::cout << "Ваш выбор: ";
    std::cin >> ticketTypeChoice;
    std::cin.ignore();

    // Преобразуем ввод в Ticket::TicketType
    Ticket::TicketType ticketType;
    switch (ticketTypeChoice) {
    case 0:
        ticketType = Ticket::TicketType::ADULT;
        break;
    case 1:
        ticketType = Ticket::TicketType::CHILD;
        break;
    case 2:
        ticketType = Ticket::TicketType::LUGGAGE;
        break;
    default:
        std::cout << "Неверный тип билета! Будет выбран взрослый билет.\n";
        ticketType = Ticket::TicketType::ADULT;
        break;
    }

    // 9. Создаем пассажира (самого пользователя)
    Passenger passenger(GetSurname(), GetName(), GetFatName(),
        GetPassportSeries(), GetPassportNumber(), GetEmail());

    // 10. Бронируем билет (исправлено)
    ticketChooser.TicketToOrder(*userOrder, seatNumber, passenger, ticketType);
}

void User::ViewMyOrder() const {
    if (!userOrder || userOrder->IsEmpty()) {
        std::cout << "У вас нет активных заказов.\n";
        return;
    }

    std::cout << "=== ВАШ ЗАКАЗ ===\n";
    userOrder->PrintOrderInfo();
}