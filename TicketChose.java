import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TicketChose {
    private Trip currentTrip;
    private List<Integer> availableSeats;  

    public TicketChose(Trip trip) {
        this.currentTrip = trip;
        this.availableSeats = new ArrayList<>();
        
        
        int totalSeats = trip.getBus().getPlaces();
        for (int i = 1; i <= totalSeats; i++) {
            availableSeats.add(i);
        }
    }

    public void showAvailableSeats() {
        System.out.println("=== Available Seats ===");
        System.out.println("Bus: " + currentTrip.getBus().getBrand() 
            + " [" + currentTrip.getBus().getCode() + "]");      
        System.out.println("Total seats: " + currentTrip.getBus().getPlaces()  
            + ", available: " + availableSeats.size() + "\n");

        if (availableSeats.isEmpty()) {
            System.out.println("No available seats!");
        } else {
            for (int seat : availableSeats) {
                System.out.println("Seat " + seat + " - Available");
            }
        }
        System.out.println("=======================");
    }

    public boolean isSeatAvailable(int seatNumber) {
        return availableSeats.contains(seatNumber);
    }

    public boolean reserveSeat(int seatNumber) {
        if (!availableSeats.contains(seatNumber)) {
            return false;  
        }
        availableSeats.remove(Integer.valueOf(seatNumber));
        return true;
    }

    public void releaseSeat(int seatNumber) {
        if (!isSeatAvailable(seatNumber)) {
            availableSeats.add(seatNumber);
            Collections.sort(availableSeats);
        }
    }

    public void ticketToOrder(Order order, int seatNumber, Passenger passenger, Ticket.TicketType ticketType) {
        // проверка доступности места
        if (!availableSeats.contains(seatNumber)) {
            System.out.println("Seat " + seatNumber + " is already taken or doesn't exist!");
            return;
        }

        // Удаление места из доступных
        availableSeats.remove(Integer.valueOf(seatNumber));

        // Создание нового билета
        Ticket newTicket = new Ticket(seatNumber, currentTrip, passenger, ticketType);

        // Добавление билета в заказ
        order.addTicket(newTicket);

        System.out.println("Ticket booked!");
        System.out.println("Seat: " + seatNumber);
        System.out.println("Type: " + newTicket.getTicketTypeName());
        System.out.println("Price: " + newTicket.getFinalPrice() + " rub.");
        System.out.println("Status: " + newTicket.getStatus());
    }

    // Informational methods
    public List<Integer> getAvailableSeats() {
        return availableSeats;
    }

    public Trip getCurrentTrip() {
        return currentTrip;
    }
}