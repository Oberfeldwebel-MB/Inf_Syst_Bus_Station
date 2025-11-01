#include "Search.hpp"

// Поиск в расписании 

std::vector<Trip*> Search::SearchTripsByDate(const Timing& timing, const std::string& date) {
    const auto& trips = timing.GetTripList();  
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        if (trip.GetRoute().find(date) != std::string::npos) {
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

std::vector<Trip*> Search::SearchTripsByRoute(const Timing& timing, const std::string& start, const std::string& finish) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    std::string target_route = start + " - " + finish;
    for (const auto& trip : trips) {
        if (trip.GetRoute() == target_route) {
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

std::vector<Trip*> Search::SearchTripsByDriver(const Timing& timing, const std::string& driverName) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        if (trip.GetDriver() && trip.GetDriver()->GetFullName().find(driverName) != std::string::npos) {
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

std::vector<Trip*> Search::SearchTripsByBus(const Timing& timing, const std::string& busCode) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        if (trip.GetBus() && trip.GetBus()->GetCode() == busCode) { 
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

std::vector<Trip*> Search::SearchTripsCombined(const Timing& timing,
    const std::string& start,
    const std::string& finish,
    const std::string& date) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        bool matches = true;

        if (!start.empty() && trip.GetRoute().find(start) == std::string::npos) {
            matches = false;
        }
        if (!finish.empty() && trip.GetRoute().find(finish) == std::string::npos) {
            matches = false;
        }
        if (!date.empty() && trip.GetRoute().find(date) == std::string::npos) {
            matches = false;
        }

        if (matches) {
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

//Поиск в заказах

std::vector<Ticket*> Search::SearchTickets(const Order& order,
    const std::string& passengerName,
    const std::string& route,
    int seatNumber,
    Ticket::TicketType ticketType) {

    // Получаем все билеты из заказа
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;

    // Если заказ пустой, сразу возвращаем пустой результат
    if (tickets.empty()) {
        return result;
    }

    // Перебираем все билеты в заказе
    for (const auto& ticket : tickets) {
        bool matches = true;

        // Проверка имени пассажира (если параметр не пустой)
        if (!passengerName.empty()) {
            std::string ticketPassenger = ticket.GetPassenger().GetFullName();
            // Ищем частичное совпадение
            if (ticketPassenger.find(passengerName) == std::string::npos) {  // Исправлено -1 на npos
                matches = false;
            }
        }

        // Проверка маршрута (если параметр не пустой)
        if (matches && !route.empty()) {
            if (ticket.GetTrip().GetRoute().find(route) == std::string::npos) {
                matches = false;
            }
        }

        // Проверка номера места (если параметр не -1)
        if (matches && seatNumber != -1) {
            if (ticket.GetPlaceNumber() != seatNumber) {
                matches = false;
            }
        }

        // Проверка типа билета (всегда проверяем, так как enum имеет значения по умолчанию)
        if (matches) {
            if (ticket.GetTicketType() != ticketType) {  // Исправлено - проверяем переданный ticketType
                matches = false;
            }
        }

        if (matches) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }

    return result;
}

std::vector<Ticket*> Search::SearchTicketsByRoute(const Order& order, const std::string& route) {
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;
    for (const auto& ticket : tickets) {
        if (ticket.GetTrip().GetRoute().find(route) != std::string::npos) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }
    return result;
}

std::vector<Ticket*> Search::SearchTicketsByType(const Order& order, Ticket::TicketType ticketType) {
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;
    for (const auto& ticket : tickets) {
        if (ticket.GetTicketType() == ticketType) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }
    return result;
}

std::vector<Ticket*> Search::SearchTicketsBySeat(const Order& order, int seatNumber) {
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;
    for (const auto& ticket : tickets) {
        if (ticket.GetPlaceNumber() == seatNumber) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }
    return result;
}


