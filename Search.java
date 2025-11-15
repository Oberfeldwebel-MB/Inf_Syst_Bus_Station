import java.util.ArrayList;
import java.util.List;

public class Search {
    private String searchDeparture;
    private String searchDestination;
    private String searchDate;

    public Search(String departure, String destination, String date) {
        this.searchDeparture = departure;
        this.searchDestination = destination;
        this.searchDate = date;
    }

    

    // Поиск в расписании (Timing)
    public List<Trip> searchTripsByDate(Timing timing, String date) {
        List<Trip> trips = timing.getTripList();
        List<Trip> result = new ArrayList<>();
        for (Trip trip : trips) {
            if (trip.getRoute().contains(date)) {
                result.add(trip);
            }
        }
        return result;
    }

    public List<Trip> searchTripsByRoute(Timing timing, String start, String finish) {
        List<Trip> trips = timing.getTripList();
        List<Trip> result = new ArrayList<>();
        String targetRoute = start + " - " + finish;
        for (Trip trip : trips) {
            if (trip.getRoute().equals(targetRoute)) {
                result.add(trip);
            }
        }
        return result;
    }

    public List<Trip> searchTripsByDriver(Timing timing, String driverName) {
        List<Trip> trips = timing.getTripList();
        List<Trip> result = new ArrayList<>();
        for (Trip trip : trips) {
            if (trip.getDriver() != null && trip.getDriver().getFullName().contains(driverName)) {
                result.add(trip);
            }
        }
        return result;
    }

    public List<Trip> searchTripsByBus(Timing timing, String busCode) {
        List<Trip> trips = timing.getTripList();
        List<Trip> result = new ArrayList<>();
        for (Trip trip : trips) {
            if (trip.getBus() != null && trip.getBus().getCode().equals(busCode)) {
                result.add(trip);
            }
        }
        return result;
    }

    public List<Trip> searchTripsCombined(Timing timing, String start, String finish, String date) {
        List<Trip> trips = timing.getTripList();
        List<Trip> result = new ArrayList<>();
        for (Trip trip : trips) {
            boolean matches = true;

            if (!start.isEmpty() && !trip.getRoute().contains(start)) {
                matches = false;
            }
            if (!finish.isEmpty() && !trip.getRoute().contains(finish)) {
                matches = false;
            }
            if (!date.isEmpty() && !trip.getRoute().contains(date)) {
                matches = false;
            }

            if (matches) {
                result.add(trip);
            }
        }
        return result;
    }

    // Поиск в заказах (Order)
    public List<Ticket> searchTicketsByPassenger(Order order, String passengerName) {
        List<Ticket> tickets = order.getTicketList();
        List<Ticket> result = new ArrayList<>();
        for (Ticket ticket : tickets) {
            if (ticket.getPassenger().getFullName().contains(passengerName)) {
                result.add(ticket);
            }
        }
        return result;
    }

    public List<Ticket> searchTicketsByRoute(Order order, String route) {
        List<Ticket> tickets = order.getTicketList();
        List<Ticket> result = new ArrayList<>();
        for (Ticket ticket : tickets) {
            if (ticket.getTrip().getRoute().contains(route)) {
                result.add(ticket);
            }
        }
        return result;
    }

    public List<Ticket> searchTicketsByType(Order order, Ticket.TicketType ticketType) {
        List<Ticket> tickets = order.getTicketList();
        List<Ticket> result = new ArrayList<>();
        for (Ticket ticket : tickets) {
            if (ticket.getTicketType() == ticketType) {
                result.add(ticket);
            }
        }
        return result;
    }

    public List<Ticket> searchTicketsBySeat(Order order, int seatNumber) {
        List<Ticket> tickets = order.getTicketList();
        List<Ticket> result = new ArrayList<>();
        for (Ticket ticket : tickets) {
            if (ticket.getPlaceNumber() == seatNumber) {
                result.add(ticket);
            }
        }
        return result;
    }

    public List<Ticket> searchTickets(Order order, String passengerName, String route, 
                                     int seatNumber, Ticket.TicketType ticketType) {
        List<Ticket> tickets = order.getTicketList();
        List<Ticket> result = new ArrayList<>();

        if (tickets.isEmpty()) {
            return result;
        }

        for (Ticket ticket : tickets) {
            boolean matches = true;

            if (!passengerName.isEmpty() && !ticket.getPassenger().getFullName().contains(passengerName)) {
                matches = false;
            }

            if (matches && !route.isEmpty() && !ticket.getTrip().getRoute().contains(route)) {
                matches = false;
            }

            if (matches && seatNumber != -1 && ticket.getPlaceNumber() != seatNumber) {
                matches = false;
            }

            if (matches && ticket.getTicketType() != ticketType) {
                matches = false;
            }

            if (matches) {
                result.add(ticket);
            }
        }

        return result;
    }
}