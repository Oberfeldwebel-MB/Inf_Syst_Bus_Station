import java.util.List;
import java.util.Scanner;

public class User extends People {
    private Order userOrder;
    private Search search;
    private Timing timing;
    

    public User(String surname, String name, String middleName,
                String passportSeries, String passportNumber, String email,
                Timing timing) {
        super(surname, name, middleName, passportSeries, passportNumber, email);
        
        // Валидация параметров
        if (timing == null) {
            throw new IllegalArgumentException("Timing cannot be null!");
        }
        
        this.search = new Search("", "", "");
        this.timing = timing;
        this.userOrder = null;
    }
    
    public void initializeOrder(TicketChose ticketChose) {
        try {
            if (ticketChose == null) {
                throw new IllegalArgumentException("TicketChose cannot be null!");
            }
            
            this.userOrder = new Order(ticketChose);
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error initializing order: " + e.getMessage());
            throw e;
        }
    }

    public void searchAndBookTicket() {
        try {
            if (this.timing == null) {
                throw new IllegalStateException("Schedule not available!");
            }

            System.out.println("=== SEARCH AND BOOK TICKET ===");

            // 1. Ввод данных
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter departure point: ");
            String start = scanner.nextLine();
            
            if (start == null || start.trim().isEmpty()) {
                throw new IllegalArgumentException("Departure point cannot be empty!");
            }
            
            System.out.print("Enter destination: ");
            String finish = scanner.nextLine();
            
            if (finish == null || finish.trim().isEmpty()) {
                throw new IllegalArgumentException("Destination cannot be empty!");
            }

            // Поиск по маршруту
            List<Trip> foundTrips = this.search.searchTripsByRoute(this.timing, start, finish);

            if (foundTrips.isEmpty()) {
                throw new IllegalStateException("Trips for route " + start + " - " + finish + " not found!");
            }

            // 2. Демонстрация найденных поездок
            System.out.println("\n=== FOUND TRIPS ===");
            for (int i = 0; i < foundTrips.size(); ++i) {
                System.out.print((i + 1) + ". ");
                foundTrips.get(i).printTripInfo();
            }

            // 3. Выбор поездки
            System.out.print("Choose trip (1-" + foundTrips.size() + "): ");
            int tripChoice = scanner.nextInt();
            scanner.nextLine(); 

            if (tripChoice < 1 || tripChoice > foundTrips.size()) {
                throw new IllegalArgumentException("Invalid choice! Please select between 1 and " + foundTrips.size());
            }

            Trip selectedTrip = foundTrips.get(tripChoice - 1);

            // 4. TicketChose для выбранной поездки
            TicketChose ticketChooser = new TicketChose(selectedTrip);

            // 5. Initialize order
            if (this.userOrder == null) {
                this.initializeOrder(ticketChooser);
            }

            // 6. Show available seats
            ticketChooser.showAvailableSeats();

            // 7. Выбор номера места
            System.out.print("Choose seat number: ");
            int seatNumber = scanner.nextInt();
            scanner.nextLine(); 
            
            if (seatNumber <= 0) {
                throw new IllegalArgumentException("Seat number must be positive!");
            }

            // 8. Выбор типа билета
            System.out.println("Choose ticket type:");
            System.out.println("0 - Adult");
            System.out.println("1 - Child");
            System.out.println("2 - Luggage");
            System.out.print("Your choice: ");
            int ticketTypeChoice = scanner.nextInt();
            scanner.nextLine(); 

            Ticket.TicketType ticketType;
            switch (ticketTypeChoice) {
                case 0:
                    ticketType = Ticket.TicketType.ADULT;
                    break;
                case 1:
                    ticketType = Ticket.TicketType.CHILD;
                    break;
                case 2:
                    ticketType = Ticket.TicketType.LUGGAGE;
                    break;
                default:
                    throw new IllegalArgumentException("Invalid ticket type! Please select 0, 1 or 2.");
            }

            // 9. Создание объекта пассажир
            Passenger passenger = new Passenger(this.getSurname(), this.getName(), this.getMiddleName(),
                    this.getPassportSeries(), this.getPassportNumber(), this.getEmail());

            // 10. Бронирование билета
            ticketChooser.ticketToOrder(this.userOrder, seatNumber, passenger, ticketType);
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error in search and book: " + e.getMessage());
        }
    }

    public void viewMyOrder() {
        try {
            if (this.userOrder == null || this.userOrder.isEmpty()) {
                System.out.println("You have no active orders.");
                return;
            }

            System.out.println("=== YOUR ORDER ===");
            this.userOrder.printOrderInfo();
            
        } catch (Exception e) {
            System.err.println("Error viewing order: " + e.getMessage());
        }
    }

    public Order getOrder() {
        return this.userOrder;
    }

    public void setTiming(Timing timing) {
        if (timing == null) {
            throw new IllegalArgumentException("Timing cannot be null!");
        }
        this.timing = timing;
    }

    public Timing getTiming() {
        return this.timing;
    }
}