public class Ticket {
    public enum TicketType {
        ADULT,      
        CHILD,      
        LUGGAGE     
    }

    private int placeNumber;
    private Trip tripData;
    private Passenger passengerData;
    private boolean ticketAvailable;
    private String ticketStatus;
    private double finalPrice;
    private TicketType type;

    public Ticket(int placeNumber, Trip trip, Passenger passenger, TicketType type) {
        this.placeNumber = placeNumber;
        this.tripData = trip;
        this.passengerData = passenger;
        this.type = type;
        this.ticketAvailable = true;
        this.ticketStatus = "Booked";
        calculateFinalPrice();
    }

    public void calculateFinalPrice() {
        double basePrice = tripData.getPrice();
        double discountMultiplier = 1.0;

        switch (type) {
            case ADULT:
                discountMultiplier = 1.0;  
                break;
            case CHILD:
                discountMultiplier = 0.5;  
                break;
            case LUGGAGE:
                discountMultiplier = 0.3;  
                break;
        }

        finalPrice = basePrice * discountMultiplier;
    }

    public String getTicketTypeName() {
        switch (type) {
            case ADULT:
                return "Adult";
            case CHILD:
                return "Child";
            case LUGGAGE:
                return "Luggage";
            default:
                return "Unknown";
        }
    }

    public void printTicketInfo() {
        System.out.println("=== Ticket Information ===");
        System.out.println("Seat: " + placeNumber);
        System.out.println("Type: " + getTicketTypeName());
        System.out.println("Route: " + tripData.getRoute());
        System.out.println("Price: " + finalPrice + " rub.");
        System.out.println("Passenger: " + passengerData.getFullName());
        System.out.println("Ticket status: " + ticketStatus);

        // Информация по автобусу и водителю
        System.out.println(tripData.getBus() != null ? 
            "Bus: " + tripData.getBus().getBrand() + " [" + tripData.getBus().getCode() + "]" : 
            "Bus: not assigned");

        System.out.println(tripData.getDriver() != null ? 
            "Driver: " + tripData.getDriver().getFullName() : 
            "Driver: not assigned");

        System.out.println("==========================");
    }

    public void ticketPaid() {
        ticketStatus = "Paid";
        System.out.println("Ticket paid");
    }

    // Геттеры
    public int getPlaceNumber() {
        return placeNumber;
    }

    public Trip getTrip() {
        return tripData;
    }

    public Passenger getPassenger() {
        return passengerData;
    }

    public TicketType getTicketType() {
        return type;
    }

    public boolean isAvailable() {
        return ticketAvailable;
    }

    public String getStatus() {
        return ticketStatus;
    }

    public double getFinalPrice() {
        return finalPrice;
    }

    public double getPrice() {
        return finalPrice;
    }

    // Сеттеры
    public void setPlaceNumber(int placeNumber) {
        this.placeNumber = placeNumber;
    }

    public void setTripData(Trip tripData) {
        this.tripData = tripData;
    }

    public void setPassengerData(Passenger passengerData) {
        this.passengerData = passengerData;
    }

    public void setTicketAvailable(boolean ticketAvailable) {
        this.ticketAvailable = ticketAvailable;
    }

    public void setTicketStatus(String ticketStatus) {
        this.ticketStatus = ticketStatus;
    }

    public void setType(TicketType type) {
        this.type = type;
        calculateFinalPrice(); 
    }
}