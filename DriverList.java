import java.util.ArrayList;
import java.util.List;

public class DriverList {
    private List<Driver> drivers;

    public DriverList() {
        this.drivers = new ArrayList<>();
    }

    public List<Driver> getDrivers() {
        return drivers;
    }

    public void addDriver(Driver driver) {
        drivers.add(driver);
        System.out.println("[DriverList] Driver " + driver.getFullName() + " added to list");
    }

    public Driver findDriverByName(String fullName) {
        for (Driver driver : drivers) {
            if (driver.getFullName().equals(fullName)) {
                return driver;
            }
        }
        return null;
    }

    public boolean removeDriver(String fullName) {
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers.get(i).getFullName().equals(fullName)) {
                System.out.println("[DriverList] Driver " + fullName + " removed");
                drivers.remove(i);
                return true;
            }
        }
        return false;
    }

    public void displayAllDrivers() {
        System.out.println("=== Driver List ===");
        for (Driver driver : drivers) {
            driver.printInfo();
            System.out.println("Current trip: " + driver.getDriverCurrentTrip() + 
                             " Status: " + (driver.getAvailability() ? "Available" : "Busy") + "\n");
        }
        System.out.println("===================");
    }
}