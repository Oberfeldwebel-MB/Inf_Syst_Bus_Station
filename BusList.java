import java.util.ArrayList;
import java.util.List;

public class BusList {
    private List<Bus> buses;

    public BusList() {
        this.buses = new ArrayList<>();
    }

    public List<Bus> getBuses() {
        return buses;
    }

    public void addBus(Bus bus) {
        buses.add(bus);
        System.out.println("[BusList] Bus " + bus.getCode() + " added to list");
    }

    public boolean removeBus(String code) {
        for (int i = 0; i < buses.size(); i++) {
            if (buses.get(i).getCode().equals(code)) {
                System.out.println("[BusList] Bus " + code + " removed");
                buses.remove(i);
                return true;
            }
        }
        System.out.println("[BusList] Bus with code " + code + " not found");
        return false;
    }

    public Bus findBusByCode(String code) {
        for (Bus bus : buses) {
            if (bus.getCode().equals(code)) {
                return bus;
            }
        }
        return null;
    }

    public void displayAllBuses() {
        System.out.println("=== Bus List ===");
        if (buses.isEmpty()) {
            System.out.println("Bus list is empty");
        } else {
            for (Bus bus : buses) {
                System.out.println("[" + bus.getCode() + "] " + bus.getBrand()
                        + " " + bus.getModel() + " (" + bus.getPlaces() + " seats) - "
                        + (bus.getAvailability() ? "Available" : "Not available"));
            }
        }
        System.out.println("================");
    }
}