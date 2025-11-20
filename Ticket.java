import java.util.Map;

public class Ticket {
    public enum TicketType {
        ADULT,      
        CHILD,      
        LUGGAGE     
    }

    // Статическое поле - коэффициенты скидок для каждого типа билета
    private static final Map<TicketType, Double> DISCOUNT_COEFFICIENTS = 
        Map.of(
            TicketType.ADULT, 1.0,   
            TicketType.CHILD, 0.5,   
            TicketType.LUGGAGE, 0.3   
        );

    private int placeNumber;
    private Trip tripData;
    private Passenger passengerData;
    private boolean ticketAvailable;
    private String ticketStatus;
    private double finalPrice;
    private TicketType type;

    public Ticket(int placeNumber, Trip trip, Passenger passenger, TicketType type) {
        // Валидация параметров
        if (placeNumber <= 0) {
            throw new IllegalArgumentException("Place number must be positive!");
        }
        if (trip == null) {
            throw new IllegalArgumentException("Trip cannot be null!");
        }
        if (passenger == null) {
            throw new IllegalArgumentException("Passenger cannot be null!");
        }
        if (type == null) {
            throw new IllegalArgumentException("Ticket type cannot be null!");
        }
        
        this.placeNumber = placeNumber;
        this.tripData = trip;
        this.passengerData = passenger;
        this.type = type;
        this.ticketAvailable = true;
        this.ticketStatus = "Booked";
        
        this.calculateFinalPrice();
    }

    // Статический метод для расчета цены билета 
    public static double calculateTicketPrice(double basePrice, TicketType ticketType) {
        try {
            if (basePrice < 0) {
                throw new IllegalArgumentException("Base price cannot be negative!");
            }
            if (ticketType == null) {
                throw new IllegalArgumentException("Ticket type cannot be null!");
            }
            
            Double coefficient = DISCOUNT_COEFFICIENTS.get(ticketType);
            if (coefficient == null) {
                throw new IllegalArgumentException("Unknown ticket type: " + ticketType);
            }
            
            return basePrice * coefficient;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error calculating ticket price: " + e.getMessage());
            throw e;
        }
    }
    
    
    // Статический метод для получения названия типа билета
    public static String getTicketTypeName(TicketType type) {
        if (type == null) {
            throw new IllegalArgumentException("Ticket type cannot be null!");
        }
        
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

    public void calculateFinalPrice() {
        this.finalPrice = calculateTicketPrice(this.tripData.getPrice(), this.type);
    }

    public String getTicketTypeName() {
        return getTicketTypeName(this.type);
    }

    public void printTicketInfo() {
        System.out.println("=== Ticket Information ===");
        System.out.println("Seat: " + this.placeNumber);
        System.out.println("Type: " + this.getTicketTypeName());
        System.out.println("Route: " + this.tripData.getRoute());
        System.out.println("Price: " + this.finalPrice + " rub.");
        System.out.println("Passenger: " + this.passengerData.getFullName());
        System.out.println("Ticket status: " + this.ticketStatus);

        // Информация по автобусу и водителю
        System.out.println(this.tripData.getBus() != null ? 
            "Bus: " + this.tripData.getBus().getBrand() + " [" + this.tripData.getBus().getCode() + "]" : 
            "Bus: not assigned");

        System.out.println(this.tripData.getDriver() != null ? 
            "Driver: " + this.tripData.getDriver().getFullName() : 
            "Driver: not assigned");

        System.out.println("==========================");
    }

    public void ticketPaid() {
        this.ticketStatus = "Paid";
        System.out.println("Ticket paid");
    }

    // Геттеры
    public int getPlaceNumber() {
        return this.placeNumber;
    }

    public Trip getTrip() {
        return this.tripData;
    }

    public Passenger getPassenger() {
        return this.passengerData;
    }

    public TicketType getTicketType() {
        return this.type;
    }

    public boolean isAvailable() {
        return this.ticketAvailable;
    }

    public String getStatus() {
        return this.ticketStatus;
    }

    public double getFinalPrice() {
        return this.finalPrice;
    }

    public double getPrice() {
        return this.finalPrice;
    }

    // Сеттеры с валидацией
    public void setPlaceNumber(int placeNumber) {
        if (placeNumber <= 0) {
            throw new IllegalArgumentException("Place number must be positive!");
        }
        this.placeNumber = placeNumber;
    }

    public void setTripData(Trip tripData) {
        if (tripData == null) {
            throw new IllegalArgumentException("Trip cannot be null!");
        }
        this.tripData = tripData;
        this.calculateFinalPrice(); 
    }

    public void setPassengerData(Passenger passengerData) {
        if (passengerData == null) {
            throw new IllegalArgumentException("Passenger cannot be null!");
        }
        this.passengerData = passengerData;
    }

    public void setTicketAvailable(boolean ticketAvailable) {
        this.ticketAvailable = ticketAvailable;
    }

    public void setTicketStatus(String ticketStatus) {
        if (ticketStatus == null || ticketStatus.trim().isEmpty()) {
            throw new IllegalArgumentException("Ticket status cannot be null or empty!");
        }
        this.ticketStatus = ticketStatus;
    }

    public void setType(TicketType type) {
        if (type == null) {
            throw new IllegalArgumentException("Ticket type cannot be null!");
        }
        this.type = type;
        this.calculateFinalPrice(); 
    }
}