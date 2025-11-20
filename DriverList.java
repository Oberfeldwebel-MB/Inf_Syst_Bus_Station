import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class DriverList {
    private List<Driver> drivers;
    
    public DriverList() {
        this.drivers = new ArrayList<>();
    }

    public List<Driver> getDrivers() {
        return this.drivers;
    }

    public void addDriver(Driver driver) {
        try {
            // Валидация входных параметров
            if (driver == null) {
                throw new IllegalArgumentException("Driver cannot be null!");
            }
            
            this.drivers.add(driver);
            System.out.println("[DriverList] Driver " + driver.getFullName() + " added to list");
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error adding driver: " + e.getMessage());
            throw e;
        }
    }

    public Driver findDriverByName(String fullName) {
        try {
            if (fullName == null || fullName.trim().isEmpty()) {
                throw new IllegalArgumentException("Driver full name cannot be null or empty!");
            }
            
            for (Driver driver : this.drivers) {
                if (driver.getFullName().equals(fullName)) {
                    return driver;
                }
            }
            return null;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error finding driver: " + e.getMessage());
            return null;
        }
    }

    public boolean removeDriver(String fullName) {
        try {
            if (fullName == null || fullName.trim().isEmpty()) {
                throw new IllegalArgumentException("Driver full name cannot be null or empty!");
            }
            
            Iterator<Driver> iterator = this.drivers.iterator();
            while (iterator.hasNext()) {
                Driver driver = iterator.next();
                if (driver.getFullName().equals(fullName)) {
                    iterator.remove();
                    System.out.println("[DriverList] Driver " + fullName + " removed");
                    return true;
                }
            }
            
            System.out.println("[DriverList] Driver '" + fullName + "' not found");
            return false;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error removing driver: " + e.getMessage());
            return false;
        }
    }

    public void displayAllDrivers() {
        System.out.println("=== Driver List ===");
        for (Driver driver : this.drivers) {
            driver.printInfo();
            System.out.println("Current trip: " + driver.getDriverCurrentTrip() + 
                             " Status: " + (driver.getAvailability() ? "Available" : "Busy") + "\n");
        }
        System.out.println("===================");
    }
}