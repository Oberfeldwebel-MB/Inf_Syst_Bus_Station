#include "User.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

void User::InitializeOrder(std::shared_ptr<TicketChose> ticketChose) {
    try {
        if (!ticketChose) {
            throw std::invalid_argument("TicketChose не может быть пустым!");
        }

        userOrder = std::make_shared<Order>(ticketChose);
        std::cout << "Заказ инициализирован для пользователя: " << GetFullName() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка инициализации заказа: " << e.what() << "\n";
        throw;
    }
}

void User::SearchAndBookTicket() {
    try {
        if (!timing) {
            throw std::runtime_error("Расписание не доступно!");
        }

        std::cout << "=== ПОИСК И БРОНИРОВАНИЕ БИЛЕТА ===\n";
        std::cout << "Пользователь: " << GetFullName() << "\n";

        // 1. Поиск поездок
        std::string start, finish;
        std::cout << "Введите пункт отправления: ";
        std::getline(std::cin, start);

        if (start.empty()) {
            throw std::invalid_argument("Пункт отправления не может быть пустым!");
        }

        std::cout << "Введите пункт назначения: ";
        std::getline(std::cin, finish);

        if (finish.empty()) {
            throw std::invalid_argument("Пункт назначения не может быть пустым!");
        }

        // Ищем поездки по маршруту
        std::vector<std::shared_ptr<Trip>> foundTrips = search.SearchTripsByRoute(*timing, start, finish);

        if (foundTrips.empty()) {
            throw std::runtime_error("Поездки по маршруту " + start + " - " + finish + " не найдены!");
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

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::invalid_argument("Неверный ввод! Ожидается число.");
        }

        std::cin.ignore();

        if (tripChoice < 1 || tripChoice > foundTrips.size()) {
            throw std::invalid_argument("Неверный выбор поездки!");
        }

        std::shared_ptr<Trip> selectedTrip = foundTrips[tripChoice - 1];

        // 4. TicketChose для выбранной поездки
        std::shared_ptr<TicketChose> ticketChooser = std::make_shared<TicketChose>(*selectedTrip);

        // 5. Инициализация заказа
        if (!userOrder) {
            InitializeOrder(ticketChooser);
        }

        // 6. Показываем доступные места
        ticketChooser->ShowAvailableSeats();

        // 7. Выбор места
        int seatNumber;
        std::cout << "Выберите номер места: ";
        std::cin >> seatNumber;

        if (std::cin.fail() || seatNumber <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::invalid_argument("Неверный номер места!");
        }

        std::cin.ignore();

        // 8. Выбор типа билета
        std::cout << "Выберите тип билета:\n";
        std::cout << "0 - Взрослый\n1 - Детский\n2 - Багажный\n";
        int ticketTypeChoice;
        std::cout << "Ваш выбор: ";
        std::cin >> ticketTypeChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::invalid_argument("Неверный ввод типа билета!");
        }

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

        // 10. Бронируем билет
        ticketChooser->TicketToOrder(userOrder, seatNumber, passenger, ticketType);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска и бронирования билета: " << e.what() << "\n";
    }
}

void User::ViewMyOrder() const {
    try {
        if (!userOrder || userOrder->IsEmpty()) {
            std::cout << "У вас нет активных заказов.\n";
            return;
        }

        std::cout << "=== ВАШ ЗАКАЗ ===\n";
        userOrder->PrintOrderInfo();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка просмотра заказа: " << e.what() << "\n";
    }
}