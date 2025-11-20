#include "Search.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

// Поиск в расписании по дате
std::vector<std::shared_ptr<Trip>> Search::SearchTripsByDate(const Timing& timing, const std::string& date) {
    try {
        if (date.empty()) {
            throw std::invalid_argument("Дата для поиска не может быть пустой!");
        }

        const auto& trips = timing.GetTripList();
        std::vector<std::shared_ptr<Trip>> result;

        for (const auto& trip : trips) {
            if (trip && trip->GetRoute().find(date) != std::string::npos) { // Исправлено на ->
                result.push_back(trip); // Просто добавляем существующий shared_ptr
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска по дате: " << e.what() << "\n";
        return {};
    }
}

// Поиск в расписании по маршруту
std::vector<std::shared_ptr<Trip>> Search::SearchTripsByRoute(const Timing& timing, const std::string& start, const std::string& finish) {
    try {
        if (start.empty() || finish.empty()) {
            throw std::invalid_argument("Пункты отправления и назначения не могут быть пустыми!");
        }

        const auto& trips = timing.GetTripList();
        std::vector<std::shared_ptr<Trip>> result;
        std::string target_route = start + " - " + finish;

        for (const auto& trip : trips) {
            if (trip && trip->GetRoute() == target_route) { // Исправлено на ->
                result.push_back(trip); // Просто добавляем существующий shared_ptr
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска по маршруту: " << e.what() << "\n";
        return {};
    }
}

// Поиск в расписании по водителю
std::vector<std::shared_ptr<Trip>> Search::SearchTripsByDriver(const Timing& timing, const std::string& driverName) {
    try {
        if (driverName.empty()) {
            throw std::invalid_argument("Имя водителя не может быть пустым!");
        }

        const auto& trips = timing.GetTripList();
        std::vector<std::shared_ptr<Trip>> result;

        for (const auto& trip : trips) {
            if (trip && trip->GetDriver() && trip->GetDriver()->GetFullName().find(driverName) != std::string::npos) { // Исправлено на ->
                result.push_back(trip); // Просто добавляем существующий shared_ptr
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска по водителю: " << e.what() << "\n";
        return {};
    }
}

// Поиск в расписании по автобусу
std::vector<std::shared_ptr<Trip>> Search::SearchTripsByBus(const Timing& timing, const std::string& busCode) {
    try {
        if (busCode.empty()) {
            throw std::invalid_argument("Код автобуса не может быть пустым!");
        }

        const auto& trips = timing.GetTripList();
        std::vector<std::shared_ptr<Trip>> result;

        for (const auto& trip : trips) {
            if (trip && trip->GetBus() && trip->GetBus()->GetCode() == busCode) { // Исправлено на ->
                result.push_back(trip); // Просто добавляем существующий shared_ptr
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска по автобусу: " << e.what() << "\n";
        return {};
    }
}

// Комбинированный поиск в расписании
std::vector<std::shared_ptr<Trip>> Search::SearchTripsCombined(const Timing& timing,
    const std::string& start,
    const std::string& finish,
    const std::string& date) {
    try {
        const auto& trips = timing.GetTripList();
        std::vector<std::shared_ptr<Trip>> result;

        for (const auto& trip : trips) {
            if (!trip) continue; // Пропускаем пустые указатели

            bool matches = true;

            if (!start.empty() && trip->GetRoute().find(start) == std::string::npos) { // Исправлено на ->
                matches = false;
            }
            if (!finish.empty() && trip->GetRoute().find(finish) == std::string::npos) { // Исправлено на ->
                matches = false;
            }
            if (!date.empty() && trip->GetRoute().find(date) == std::string::npos) { // Исправлено на ->
                matches = false;
            }

            if (matches) {
                result.push_back(trip); // Просто добавляем существующий shared_ptr
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка комбинированного поиска: " << e.what() << "\n";
        return {};
    }
}

// Поиск билетов в заказе
std::vector<std::shared_ptr<Ticket>> Search::SearchTickets(const Order& order,
    const std::string& passengerName,
    const std::string& route,
    int seatNumber,
    Ticket::TicketType ticketType) {
    try {
        const auto& tickets = order.GetTicketList();
        std::vector<std::shared_ptr<Ticket>> result;

        if (tickets.empty()) {
            return result;
        }

        for (const auto& ticket : tickets) {
            bool matches = true;

            if (!passengerName.empty()) {
                std::string ticketPassenger = ticket.GetPassenger().GetFullName();
                if (ticketPassenger.find(passengerName) == std::string::npos) {
                    matches = false;
                }
            }

            if (matches && !route.empty()) {
                if (ticket.GetTrip().GetRoute().find(route) == std::string::npos) {
                    matches = false;
                }
            }

            if (matches && seatNumber != -1) {
                if (ticket.GetPlaceNumber() != seatNumber) {
                    matches = false;
                }
            }

            if (matches) {
                if (ticket.GetTicketType() != ticketType) {
                    matches = false;
                }
            }

            if (matches) {
                result.push_back(std::shared_ptr<Ticket>(const_cast<Ticket*>(&ticket), [](Ticket*) {}));
            }
        }

        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска билетов: " << e.what() << "\n";
        return {};
    }
}

// Поиск билетов по маршруту
std::vector<std::shared_ptr<Ticket>> Search::SearchTicketsByRoute(const Order& order, const std::string& route) {
    try {
        if (route.empty()) {
            throw std::invalid_argument("Маршрут для поиска не может быть пустым!");
        }

        const auto& tickets = order.GetTicketList();
        std::vector<std::shared_ptr<Ticket>> result;

        for (const auto& ticket : tickets) {
            if (ticket.GetTrip().GetRoute().find(route) != std::string::npos) {
                result.push_back(std::shared_ptr<Ticket>(const_cast<Ticket*>(&ticket), [](Ticket*) {}));
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска билетов по маршруту: " << e.what() << "\n";
        return {};
    }
}

// Поиск билетов по типу
std::vector<std::shared_ptr<Ticket>> Search::SearchTicketsByType(const Order& order, Ticket::TicketType ticketType) {
    try {
        const auto& tickets = order.GetTicketList();
        std::vector<std::shared_ptr<Ticket>> result;

        for (const auto& ticket : tickets) {
            if (ticket.GetTicketType() == ticketType) {
                result.push_back(std::shared_ptr<Ticket>(const_cast<Ticket*>(&ticket), [](Ticket*) {}));
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска билетов по типу: " << e.what() << "\n";
        return {};
    }
}

// Поиск билетов по месту
std::vector<std::shared_ptr<Ticket>> Search::SearchTicketsBySeat(const Order& order, int seatNumber) {
    try {
        if (seatNumber <= 0) {
            throw std::invalid_argument("Номер места должен быть положительным!");
        }

        const auto& tickets = order.GetTicketList();
        std::vector<std::shared_ptr<Ticket>> result;

        for (const auto& ticket : tickets) {
            if (ticket.GetPlaceNumber() == seatNumber) {
                result.push_back(std::shared_ptr<Ticket>(const_cast<Ticket*>(&ticket), [](Ticket*) {}));
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска билетов по месту: " << e.what() << "\n";
        return {};
    }
}

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Search& search) {
    os << "Поиск: ";

    if (!search.SearchOtp.empty()) {
        os << "от " << search.SearchOtp;
    }
    if (!search.SearchPr.empty()) {
        os << " до " << search.SearchPr;
    }
    if (!search.SearchDate.empty()) {
        os << " (" << search.SearchDate << ")";
    }

    if (search.SearchOtp.empty() && search.SearchPr.empty() && search.SearchDate.empty()) {
        os << "общий поиск";
    }

    return os;
}