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
        this.search = new Search();
        this.timing = timing;
        this.userOrder = null;
    }

    public void initializeOrder(TicketChose ticketChose) {
        this.userOrder = new Order(ticketChose);
    }

    public void searchAndBookTicket() {
        if (timing == null) {
            System.out.println("Error: schedule not available!");
            return;
        }

        System.out.println("=== SEARCH AND BOOK TICKET ===");

        // 1. Ввод данных
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter departure point: ");
        String start = scanner.nextLine();
        System.out.print("Enter destination: ");
        String finish = scanner.nextLine();

        // Поиск по маршруту
        List<Trip> foundTrips = search.searchTripsByRoute(timing, start, finish);

        if (foundTrips.isEmpty()) {
            System.out.println("Trips for route " + start + " - " + finish + " not found!");
            return;
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
            System.out.println("Invalid choice!");
            return;
        }

        Trip selectedTrip = foundTrips.get(tripChoice - 1);

        // 4. TicketChose for selected trip
        TicketChose ticketChooser = new TicketChose(selectedTrip);

        // 5. Initialize order
        if (userOrder == null) {
            initializeOrder(ticketChooser);
        }

        // 6. Show available seats
        ticketChooser.showAvailableSeats();

        // 7. Выбор номера места
        System.out.print("Choose seat number: ");
        int seatNumber = scanner.nextInt();
        scanner.nextLine(); 

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
                System.out.println("Invalid ticket type! Adult ticket will be selected.");
                ticketType = Ticket.TicketType.ADULT;
                break;
        }

        // 9. Созание объекта пассажир
        Passenger passenger = new Passenger(getSurname(), getName(), getMiddleName(),
                getPassportSeries(), getPassportNumber(), getEmail());

        // 10. объект заказа билета
        ticketChooser.ticketToOrder(userOrder, seatNumber, passenger, ticketType);
    }

    public void viewMyOrder() {
        if (userOrder == null || userOrder.isEmpty()) {
            System.out.println("You have no active orders.");
            return;
        }

        System.out.println("=== YOUR ORDER ===");
        userOrder.printOrderInfo();
    }

    public Order getOrder() {
        return userOrder;
    }

    public void setTiming(Timing timing) {
        this.timing = timing;
    }

    public Timing getTiming() {
        return timing;
    }
}