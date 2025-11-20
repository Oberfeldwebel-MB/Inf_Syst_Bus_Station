import java.util.InputMismatchException;
import java.util.Scanner;

public class Admin extends Workers {
    
    public Admin(String surname, String name, String middleName, int salary) {
        super(surname, name, middleName, salary, true); 
    }
    
    public void changeBusTiming(Timing timing) {
        // Проверка входных параметров
        if (timing == null) {
            System.err.println("Error: Timing cannot be null!");
            return;
        }
        
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.println("=== SCHEDULE MANAGEMENT ===");
            System.out.println("Admin: " + this.getFullName()); 
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
                    
                    try {
                        System.out.print("Enter departure point: ");
                        String start = scanner.nextLine();
                        if (start.trim().isEmpty()) {
                            throw new IllegalArgumentException("Departure point cannot be empty!");
                        }
                        
                        System.out.print("Enter destination: ");
                        String finish = scanner.nextLine();
                        if (finish.trim().isEmpty()) {
                            throw new IllegalArgumentException("Destination cannot be empty!");
                        }
                        
                        System.out.print("Enter ticket price: ");
                        int price = scanner.nextInt();
                        if (price <= 0) {
                            throw new IllegalArgumentException("Price must be positive!");
                        }
                        scanner.nextLine();
                        
                        Bus tripBus = this.chooseBus(); 
                        Driver tripDriver = this.chooseDriver();
                        
                        if (tripBus == null || tripDriver == null) {
                            throw new IllegalStateException("Bus or driver not found!");
                        }
                        
                        Trip newTrip = new Trip(start, finish, price, tripBus, tripDriver);
                        timing.addTrip(newTrip);
                        
                        System.out.println("Trip added successfully!");
                        
                    } catch (InputMismatchException e) {
                        System.err.println("Error: Invalid input format! Please enter correct data.");
                        scanner.nextLine(); // Очистка буфера
                    } catch (IllegalArgumentException | IllegalStateException e) {
                        System.err.println("Error: " + e.getMessage());
                    }
                    break;
                }
                    
                case 3: {
                    System.out.println("=== DELETE TRIP ===");
                    timing.displayAllTrips();
                    
                    try {
                        if (timing.getTripList().isEmpty()) {
                            System.out.println("No trips available for deletion.");
                            break;
                        }
                        
                        System.out.print("Enter trip route to delete: ");
                        String routeToDelete = scanner.nextLine();
                        
                        if (routeToDelete.trim().isEmpty()) {
                            throw new IllegalArgumentException("Route cannot be empty!");
                        }
                        
                        boolean removed = timing.removeTrip(routeToDelete);
                        if (removed) {
                            System.out.println("Trip successfully deleted!");
                        } else {
                            System.out.println("Failed to delete trip.");
                        }
                        
                    } catch (IllegalArgumentException | IllegalStateException e) {
                        System.err.println("Error: " + e.getMessage());
                    }
                    break;
                }
                    
                case 0:
                    System.out.println("Exit from schedule management");
                    break;
                    
                default:
                    System.err.println("Invalid choice! Please select 0-3.");
                    break;
            }
            
        } catch (InputMismatchException e) {
            System.err.println("Error: Invalid input! Please enter a number.");
            scanner.nextLine(); 
        } catch (Exception e) {
            System.err.println("Unexpected error: " + e.getMessage());
        }
    }
    
    public Bus chooseBus() {
        Scanner scanner = new Scanner(System.in);
        
        try {
            BusList busList = new BusList();
            busList.displayAllBuses();
            
            if (busList.getBuses().isEmpty()) {
                System.out.println("No buses available in the list.");
                return null;
            }
            
            System.out.print("Enter bus code: ");
            String selectedCodeBus = scanner.nextLine();
            
            if (selectedCodeBus.trim().isEmpty()) {
                throw new IllegalArgumentException("Bus code cannot be empty!");
            }
            
            Bus foundBus = busList.findBusByCode(selectedCodeBus);
            if (foundBus != null) {
                System.out.println("Found bus: " + foundBus.getBrand() + " " + foundBus.getModel());
                return foundBus;
            } else {
                throw new IllegalArgumentException("Bus with code '" + selectedCodeBus + "' not found!");
            }
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error: " + e.getMessage());
            return null;
        } catch (Exception e) {
            System.err.println("Unexpected error in chooseBus: " + e.getMessage());
            return null;
        }
    }
    
    public Driver chooseDriver() {
        Scanner scanner = new Scanner(System.in);
        
        try {
            DriverList driverList = new DriverList();
            driverList.displayAllDrivers();
            
            if (driverList.getDrivers().isEmpty()) {
                System.out.println("No drivers available in the list.");
                return null;
            }
            
            System.out.print("Enter driver full name: ");
            String selectedDriverName = scanner.nextLine();
            
            if (selectedDriverName.trim().isEmpty()) {
                throw new IllegalArgumentException("Driver name cannot be empty!");
            }
            
            Driver foundDriver = driverList.findDriverByName(selectedDriverName);
            if (foundDriver != null) {
                System.out.println("Found driver: " + foundDriver.getFullName() + 
                                 " (License: " + foundDriver.getLicense() + ")");
                return foundDriver;
            } else {
                throw new IllegalArgumentException("Driver '" + selectedDriverName + "' not found!");
            }
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error: " + e.getMessage());
            return null;
        } catch (Exception e) {
            System.err.println("Unexpected error in chooseDriver: " + e.getMessage());
            return null;
        }
    }
}