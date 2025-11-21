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
        try {
            if (timing == null) {
                throw new IllegalArgumentException("Timing cannot be null!");
            }
            if (date == null || date.trim().isEmpty()) {
                throw new IllegalArgumentException("Date cannot be null or empty!");
            }
            
            List<Trip> trips = timing.getTripList();
            List<Trip> result = new ArrayList<>();
            for (Trip trip : trips) {
                if (trip.getRoute().contains(date)) {
                    result.add(trip);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching trips by date: " + e.getMessage());
            return new ArrayList<>(); // Возвращаем пустой список вместо null
        }
    }

    public List<Trip> searchTripsByRoute(Timing timing, String start, String finish) {
        try {
            if (timing == null) {
                throw new IllegalArgumentException("Timing cannot be null!");
            }
            if (start == null || start.trim().isEmpty()) {
                throw new IllegalArgumentException("Start point cannot be null or empty!");
            }
            if (finish == null || finish.trim().isEmpty()) {
                throw new IllegalArgumentException("Finish point cannot be null or empty!");
            }
            
            List<Trip> trips = timing.getTripList();
            List<Trip> result = new ArrayList<>();
            String targetRoute = start + " - " + finish;
            for (Trip trip : trips) {
                if (trip.getRoute().equals(targetRoute)) {
                    result.add(trip);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching trips by route: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Trip> searchTripsByDriver(Timing timing, String driverName) {
        try {
            if (timing == null) {
                throw new IllegalArgumentException("Timing cannot be null!");
            }
            if (driverName == null || driverName.trim().isEmpty()) {
                throw new IllegalArgumentException("Driver name cannot be null or empty!");
            }
            
            List<Trip> trips = timing.getTripList();
            List<Trip> result = new ArrayList<>();
            for (Trip trip : trips) {
                if (trip.getDriver() != null && trip.getDriver().getFullName().contains(driverName)) {
                    result.add(trip);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching trips by driver: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Trip> searchTripsByBus(Timing timing, String busCode) {
        try {
            if (timing == null) {
                throw new IllegalArgumentException("Timing cannot be null!");
            }
            if (busCode == null || busCode.trim().isEmpty()) {
                throw new IllegalArgumentException("Bus code cannot be null or empty!");
            }
            
            List<Trip> trips = timing.getTripList();
            List<Trip> result = new ArrayList<>();
            for (Trip trip : trips) {
                if (trip.getBus() != null && trip.getBus().getCode().equals(busCode)) {
                    result.add(trip);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching trips by bus: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Trip> searchTripsCombined(Timing timing, String start, String finish, String date) {
        try {
            if (timing == null) {
                throw new IllegalArgumentException("Timing cannot be null!");
            }
            
            List<Trip> trips = timing.getTripList();
            List<Trip> result = new ArrayList<>();
            for (Trip trip : trips) {
                boolean matches = true;

                if (start != null && !start.trim().isEmpty() && !trip.getRoute().contains(start)) {
                    matches = false;
                }
                if (finish != null && !finish.trim().isEmpty() && !trip.getRoute().contains(finish)) {
                    matches = false;
                }
                if (date != null && !date.trim().isEmpty() && !trip.getRoute().contains(date)) {
                    matches = false;
                }

                if (matches) {
                    result.add(trip);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error in combined search: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    // Поиск в заказах (Order)
    public List<Ticket> searchTicketsByPassenger(Order order, String passengerName) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            if (passengerName == null || passengerName.trim().isEmpty()) {
                throw new IllegalArgumentException("Passenger name cannot be null or empty!");
            }
            
            List<Ticket> tickets = order.getTicketList();
            List<Ticket> result = new ArrayList<>();
            for (Ticket ticket : tickets) {
                if (ticket.getPassenger().getFullName().contains(passengerName)) {
                    result.add(ticket);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching tickets by passenger: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Ticket> searchTicketsByRoute(Order order, String route) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            if (route == null || route.trim().isEmpty()) {
                throw new IllegalArgumentException("Route cannot be null or empty!");
            }
            
            List<Ticket> tickets = order.getTicketList();
            List<Ticket> result = new ArrayList<>();
            for (Ticket ticket : tickets) {
                if (ticket.getTrip().getRoute().contains(route)) {
                    result.add(ticket);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching tickets by route: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Ticket> searchTicketsByType(Order order, Ticket.TicketType ticketType) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            
            List<Ticket> tickets = order.getTicketList();
            List<Ticket> result = new ArrayList<>();
            for (Ticket ticket : tickets) {
                if (ticket.getTicketType() == ticketType) {
                    result.add(ticket);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching tickets by type: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Ticket> searchTicketsBySeat(Order order, int seatNumber) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }
            
            List<Ticket> tickets = order.getTicketList();
            List<Ticket> result = new ArrayList<>();
            for (Ticket ticket : tickets) {
                if (ticket.getPlaceNumber() == seatNumber) {
                    result.add(ticket);
                }
            }
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error searching tickets by seat: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<Ticket> searchTickets(Order order, String passengerName, String route, 
                                     int seatNumber, Ticket.TicketType ticketType) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            
            List<Ticket> tickets = order.getTicketList();
            List<Ticket> result = new ArrayList<>();

            if (tickets.isEmpty()) {
                return result;
            }

            for (Ticket ticket : tickets) {
                boolean matches = true;

                if (passengerName != null && !passengerName.trim().isEmpty() && 
                    !ticket.getPassenger().getFullName().contains(passengerName)) {
                    matches = false;
                }

                if (matches && route != null && !route.trim().isEmpty() && 
                    !ticket.getTrip().getRoute().contains(route)) {
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
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error in complex ticket search: " + e.getMessage());
            return new ArrayList<>();
        }
    }
}