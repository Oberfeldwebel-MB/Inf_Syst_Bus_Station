#include "Search.h"

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

std::vector<Trip*> Search::SearchTripsByDriver(const Timing& timing, const std::string& driver_name) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        if (trip.GetDriver() && trip.GetDriver()->GetFullName().find(driver_name) != std::string::npos) {
            result.push_back(const_cast<Trip*>(&trip));
        }
    }
    return result;
}

std::vector<Trip*> Search::SearchTripsByBus(const Timing& timing, const std::string& bus_code) {
    const auto& trips = timing.GetTripList();
    std::vector<Trip*> result;
    for (const auto& trip : trips) {
        if (trip.GetBus() && trip.GetBus()->GetCode() == bus_code) {  // -> вместо .
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
    const std::string& passenger_name,
    const std::string& route,
    int seat_number,
    int type_index) {
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

        //Проверка имени пассажира (если параметр не пустой)
        if (!passenger_name.empty()) {
            std::string ticket_passenger = ticket.GetPassenger().GetFullName();
            // Ищем частичное совпадение (например, "Иванов" найдет "Иванов Иван Иванович")
            if (ticket_passenger.find(passenger_name) == -1) {
                matches = false;
            }
        }

        //Проверка маршрута
        if (!route.empty()) {
            if (ticket.GetTrip().GetRoute().find(route) == std::string::npos)
                  matches = false;
        }

        //Проверка типа билета
        if (type_index != -1) {
            if (ticket.GetPlaceNumber() != seat_number)
                matches = false;
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

std::vector<Ticket*> Search::SearchTicketsByType(const Order& order, int type_index) {
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;
    for (const auto& ticket : tickets) {
        if (ticket.GetTicketTypeIndex() == type_index) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }
    return result;
}

std::vector<Ticket*> Search::SearchTicketsBySeat(const Order& order, int seat_number) {
    const auto& tickets = order.GetTicketList();
    std::vector<Ticket*> result;
    for (const auto& ticket : tickets) {
        if (ticket.GetPlaceNumber() == seat_number) {
            result.push_back(const_cast<Ticket*>(&ticket));
        }
    }
    return result;
}


