import java.util.Iterator;
import java.util.List;

public class BusList {
    private List<Bus> buses;

    public List<Bus> getBuses() {
        return this.buses;
    }

    public void addBus(Bus bus) {
        try {
            if (bus == null) {
                throw new IllegalArgumentException("Bus cannot be null!");
            }
            
            this.buses.add(bus);
            System.out.println("[BusList] Bus " + bus.getCode() + " added to list");
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error adding bus: " + e.getMessage());
            throw e;
        }
    }

    public boolean removeBus(String code) {
        try {
            if (code == null || code.trim().isEmpty()) {
                throw new IllegalArgumentException("Bus code cannot be null or empty!");
            }
            
            Iterator<Bus> iterator = this.buses.iterator();
            while (iterator.hasNext()) {
                Bus bus = iterator.next();
                if (bus.getCode().equals(code)) {
                    iterator.remove();
                    System.out.println("[BusList] Bus " + code + " removed");
                    return true;
                }
            }
            
            System.out.println("[BusList] Bus with code " + code + " not found");
            return false;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error removing bus: " + e.getMessage());
            return false;
        }
    }

    public Bus findBusByCode(String code) {
        try {
            if (code == null || code.trim().isEmpty()) {
                throw new IllegalArgumentException("Bus code cannot be null or empty!");
            }
            
            for (Bus bus : this.buses) {
                if (bus.getCode().equals(code)) {
                    return bus;
                }
            }
            return null;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error finding bus: " + e.getMessage());
            return null;
        }
    }

    public void displayAllBuses() {
        System.out.println("=== Bus List ===");
        if (this.buses.isEmpty()) {
            System.out.println("Bus list is empty");
        } else {
            for (Bus bus : this.buses) {
                System.out.println("[" + bus.getCode() + "] " + bus.getBrand()
                        + " " + bus.getModel() + " (" + bus.getPlaces() + " seats) - "
                        + (bus.getAvailability() ? "Available" : "Not available"));
            }
        }
        System.out.println("================");
    }
}