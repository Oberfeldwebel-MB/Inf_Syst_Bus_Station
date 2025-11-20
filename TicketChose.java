import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TicketChose {
    private Trip currentTrip;
    private List<Integer> availableSeats;

    public TicketChose(Trip trip) {
        try {
            if (trip == null) {
                throw new IllegalArgumentException("Trip cannot be null!");
            }
            if (trip.getBus() == null) {
                throw new IllegalArgumentException("Trip must have a bus assigned!");
            }
            
            this.currentTrip = trip;
            this.availableSeats = new ArrayList<>();
            
            // Заполняем доступные места
            int totalSeats = trip.getBus().getPlaces();
            if (totalSeats <= 0) {
                throw new IllegalArgumentException("Bus must have positive number of seats!");
            }
            
            for (int i = 1; i <= totalSeats; i++) {
                this.availableSeats.add(i);
            }
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error creating TicketChose: " + e.getMessage());
            throw e;
        }
    }
    

    public void showAvailableSeats() {
        try {
            if (this.currentTrip == null) {
                throw new IllegalStateException("No trip assigned!");
            }
            
            System.out.println("=== Available Seats ===");
            System.out.println("Bus: " + this.currentTrip.getBus().getBrand() 
                + " [" + this.currentTrip.getBus().getCode() + "]");      
            System.out.println("Total seats: " + this.currentTrip.getBus().getPlaces()  
                + ", available: " + this.availableSeats.size() + "\n");

            if (this.availableSeats.isEmpty()) {
                System.out.println("No available seats!");
            } else {
                for (int seat : this.availableSeats) {
                    System.out.println("Seat " + seat + " - Available");
                }
            }
            System.out.println("=======================");
            
        } catch (IllegalStateException e) {
            System.err.println("Error showing available seats: " + e.getMessage());
        }
    }

    public boolean isSeatAvailable(int seatNumber) {
        try {
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }
            
            return this.availableSeats.contains(seatNumber);
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error checking seat availability: " + e.getMessage());
            return false;
        }
    }

    public boolean reserveSeat(int seatNumber) {
        try {
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }
            
            if (!this.availableSeats.contains(seatNumber)) {
                return false;  
            }
            this.availableSeats.remove(Integer.valueOf(seatNumber));
            return true;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error reserving seat: " + e.getMessage());
            return false;
        }
    }

    public void releaseSeat(int seatNumber) {
        try {
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }
            
            if (!this.isSeatAvailable(seatNumber)) {
                this.availableSeats.add(seatNumber);
                Collections.sort(this.availableSeats);
            }
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error releasing seat: " + e.getMessage());
        }
    }

    public void ticketToOrder(Order order, int seatNumber, Passenger passenger, Ticket.TicketType ticketType) {
        try {
            if (order == null) {
                throw new IllegalArgumentException("Order cannot be null!");
            }
            if (passenger == null) {
                throw new IllegalArgumentException("Passenger cannot be null!");
            }
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }
            if (ticketType == null) {
                throw new IllegalArgumentException("Ticket type cannot be null!");
            }
            
            // проверка доступности места
            if (!this.availableSeats.contains(seatNumber)) {
                throw new IllegalStateException("Seat " + seatNumber + " is already taken or doesn't exist!");
            }

            // Удаление места из доступных
            this.availableSeats.remove(Integer.valueOf(seatNumber));

            // создание нового билета
            Ticket newTicket = new Ticket(seatNumber, this.currentTrip, passenger, ticketType);

            // Добавление билета в заказ
            order.addTicket(newTicket);

            System.out.println("Ticket booked!");
            System.out.println("Seat: " + seatNumber);
            System.out.println("Type: " + newTicket.getTicketTypeName());
            System.out.println("Price: " + newTicket.getFinalPrice() + " rub.");
            System.out.println("Status: " + newTicket.getStatus());
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error booking ticket: " + e.getMessage());
            throw e;
        }
    }

    // Геттеры
    public List<Integer> getAvailableSeats() {
        return this.availableSeats;
    }

    public Trip getCurrentTrip() {
        return this.currentTrip;
    }
}