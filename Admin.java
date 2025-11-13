import java.util.Scanner;

public class Admin extends Workers {
    
    
    public Admin(String surname, String name, String middleName, int salary) {
        super(surname, name, middleName, salary, true); 
    }
    
    public void changeBusTiming(Timing timing) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("=== SCHEDULE MANAGEMENT ===");
        System.out.println("1. Show all trips");
        System.out.println("2. Add trip");
        System.out.println("3. Delete trip");
        System.out.println("0. Exit");
        System.out.print("Choose action: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();
        
        switch (choice) {
            case 1:
                timing.displayAllTrips();
                break;
                
            case 2: {
                System.out.println("=== ADD TRIP ===");
                
                System.out.print("Enter departure point: ");
                String start = scanner.nextLine();
                System.out.print("Enter destination: ");
                String finish = scanner.nextLine();
                System.out.print("Enter ticket price: ");
                int price = scanner.nextInt();
                scanner.nextLine();
                
                Bus tripBus = chooseBus();
                Driver tripDriver = chooseDriver();
                
                Trip newTrip = new Trip(start, finish, price, tripBus, tripDriver);
                timing.addTrip(newTrip);
                
                System.out.println("Trip added!");
                break;
            }
                
            case 3: {
                System.out.println("=== DELETE TRIP ===");
                timing.displayAllTrips();
                System.out.println("To delete you need to select a specific trip...");
                
                System.out.print("Enter departure point: ");
                String start = scanner.nextLine();
                System.out.print("Enter destination: ");
                String finish = scanner.nextLine();
                System.out.print("Enter ticket price: ");
                int price = scanner.nextInt();
                scanner.nextLine();
                
                Bus tripBus = chooseBus();
                Driver tripDriver = chooseDriver();
                break;
            }
                
            case 0:
                System.out.println("Exit from schedule management");
                break;
                
            default:
                System.out.println("Invalid choice!");
                break;
        }
    }
    
    public Bus chooseBus() {
        Scanner scanner = new Scanner(System.in);
        BusList busList = new BusList();
        busList.displayAllBuses();
        
        System.out.print("Enter bus code: ");
        String selectedCodeBus = scanner.nextLine();
        
        Bus foundBus = busList.findBusByCode(selectedCodeBus);
        if (foundBus != null) {
            System.out.println("Found bus: " + foundBus.getBrand() + " " + foundBus.getModel());
            return foundBus;
        } else {
            System.out.println("Bus with code '" + selectedCodeBus + "' not found!");
            return null;
        }
    }
    
    public Driver chooseDriver() {
        Scanner scanner = new Scanner(System.in);
        DriverList driverList = new DriverList();
        driverList.displayAllDrivers();
        
        System.out.print("Enter driver full name: ");
        String selectedDriverName = scanner.nextLine();
        
        Driver foundDriver = driverList.findDriverByName(selectedDriverName);
        if (foundDriver != null) {
            System.out.println("Found driver: " + foundDriver.getFullName() + 
                             " (License: " + foundDriver.getLicense() + ")");
            return foundDriver;
        } else {
            System.out.println("Driver '" + selectedDriverName + "' not found!");
            return null;
        }
    }
}