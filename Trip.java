import java.util.Scanner;

public class Trip {
    private String startPoint;
    private String finishPoint;
    private String statusTrip;
    private int priceTicket = 0;
    private Bus busData;
    private Driver driverData;
    
    // Конструктор
    public Trip(String start, String finish, int price, Bus bus, Driver driver) {
        // Валидация 
        if (start == null || start.trim().isEmpty()) {
            throw new IllegalArgumentException("Start point cannot be null or empty!");
        }
        if (finish == null || finish.trim().isEmpty()) {
            throw new IllegalArgumentException("Finish point cannot be null or empty!");
        }
        if (price <= 0) {
            throw new IllegalArgumentException("Price must be positive!");
        }
        
        this.startPoint = start;
        this.finishPoint = finish;
        this.priceTicket = price;
        this.busData = bus;
        this.driverData = driver;
        this.statusTrip = "Planned"; // Статус по умолчанию
        
    }
    
    // Публичные методы 
    public void startTrip() {
        try {
            if (this.busData == null) {
                throw new IllegalStateException("Bus is not assigned for the trip!");
            }
            if (this.driverData == null) {
                throw new IllegalStateException("Driver is not assigned for the trip!");
            }
            
            this.statusTrip = "In progress";
            System.out.println("Trip started: " + this.startPoint + " - " + this.finishPoint);
            System.out.println("Driver: " + this.driverData.getFullName());
            System.out.println("Bus: " + this.busData.getBrand() + " [" + this.busData.getCode() + "]");
            
        } catch (IllegalStateException e) {
            System.err.println("Error starting trip: " + e.getMessage());
            throw e;
        }
    }

    public void completeTrip() {
        try {
            if (!"In progress".equals(this.statusTrip)) {
                throw new IllegalStateException("Only trips in progress can be completed!");
            }
            
            this.statusTrip = "Completed";
            System.out.println("Trip completed: " + this.startPoint + " - " + this.finishPoint);
            
        } catch (IllegalStateException e) {
            System.err.println("Error completing trip: " + e.getMessage());
            throw e;
        }
    }

    public void cancelTrip() {
        try {
            if ("Completed".equals(this.statusTrip)) {
                throw new IllegalStateException("Completed trips cannot be cancelled!");
            }
            
            this.statusTrip = "Cancelled";
            System.out.println("Trip cancelled: " + this.startPoint + " - " + this.finishPoint);
            
        } catch (IllegalStateException e) {
            System.err.println("Error cancelling trip: " + e.getMessage());
            throw e;
        }
    }

    public void printTripInfo() {
        System.out.println("=== Trip Information ===");
        System.out.println("Route: " + this.startPoint + " → " + this.finishPoint);
        System.out.println("Status: " + this.statusTrip);
        System.out.println("Ticket price: " + this.priceTicket + " rub.");
        System.out.println(this.busData != null ? 
            "Bus: " + this.busData.getBrand() + " [" + this.busData.getCode() + "]" : 
            "Bus: not assigned");
            
        System.out.println(this.driverData != null ? 
            "Driver: " + this.driverData.getFullName() : 
            "Driver: not assigned");
        System.out.println("=========================");
    }

    public void changeDriver(DriverList driverList) {
        try {
            if (driverList == null) {
                throw new IllegalArgumentException("DriverList cannot be null!");
            }
            
            // Список доступных водителей
            System.out.println("=== Available Drivers ===");

            boolean foundAvailable = false;
            for (Driver driver : driverList.getDrivers()) {
                if (driver.getAvailability()) {
                    System.out.println("• " + driver.getFullName()
                        + " (License: " + driver.getLicense() + ")");
                    foundAvailable = true;
                }
            }

            if (!foundAvailable) {
                throw new IllegalStateException("No available drivers!");
            }

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter driver full name: ");
            String selectedName = scanner.nextLine();
            
            if (selectedName == null || selectedName.trim().isEmpty()) {
                throw new IllegalArgumentException("Driver name cannot be empty!");
            }

            // Поиск и установка водителя
            Driver foundDriver = driverList.findDriverByName(selectedName);
            if (foundDriver != null && foundDriver.getAvailability()) {
                this.driverData = foundDriver;
                System.out.println("Driver changed to: " + foundDriver.getFullName());
            } else {
                throw new IllegalStateException("Driver not found or unavailable!");
            }
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error changing driver: " + e.getMessage());
            throw e;
        }
    }

    public void changeBus(BusList busList) {
        try {
            if (busList == null) {
                throw new IllegalArgumentException("BusList cannot be null!");
            }
            
            // Список доступных автобусов
            System.out.println("=== Available Buses ===");

            boolean foundAvailable = false;
            for (Bus bus : busList.getBuses()) {
                if (bus.getAvailability()) {
                    System.out.println("• [" + bus.getCode() + "] " + bus.getBrand()
                        + " " + bus.getModel() + " (" + bus.getPlaces() + " seats)");
                    foundAvailable = true;
                }
            }

            if (!foundAvailable) {
                throw new IllegalStateException("No available buses!");
            }

            // Выбор автобуса
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter bus code: ");
            String selectedCode = scanner.nextLine();
            
            if (selectedCode == null || selectedCode.trim().isEmpty()) {
                throw new IllegalArgumentException("Bus code cannot be empty!");
            }

            // Поиск и установка автобуса
            Bus foundBus = busList.findBusByCode(selectedCode);
            if (foundBus != null && foundBus.getAvailability()) {
                this.busData = foundBus;
                System.out.println("Bus changed to: " + foundBus.getBrand()
                    + " [" + foundBus.getCode() + "]");
            } else {
                throw new IllegalStateException("Bus not found or unavailable!");
            }
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error changing bus: " + e.getMessage());
            throw e;
        }
    }

    // Геттеры
    public String getRoute() {
        return this.startPoint + " - " + this.finishPoint;
    }

    public String getStatus() {
        return this.statusTrip;
    }

    public int getPrice() {
        return this.priceTicket;
    }

    public Bus getBus() {
        return this.busData;
    }

    public Driver getDriver() {
        return this.driverData;
    }

    // Сеттеры
    public void setStartPoint(String startPoint) {
        if (startPoint == null || startPoint.trim().isEmpty()) {
            throw new IllegalArgumentException("Start point cannot be null or empty!");
        }
        this.startPoint = startPoint;
    }

    public void setFinishPoint(String finishPoint) {
        if (finishPoint == null || finishPoint.trim().isEmpty()) {
            throw new IllegalArgumentException("Finish point cannot be null or empty!");
        }
        this.finishPoint = finishPoint;
    }

    public void setStatusTrip(String statusTrip) {
        if (statusTrip == null || statusTrip.trim().isEmpty()) {
            throw new IllegalArgumentException("Status cannot be null or empty!");
        }
        this.statusTrip = statusTrip;
    }

    public void setPriceTicket(int priceTicket) {
        if (priceTicket <= 0) {
            throw new IllegalArgumentException("Price must be positive!");
        }
        this.priceTicket = priceTicket;
    }

    public void setBusData(Bus busData) {
        this.busData = busData;
    }

    public void setDriverData(Driver driverData) {
        this.driverData = driverData;
    }
}