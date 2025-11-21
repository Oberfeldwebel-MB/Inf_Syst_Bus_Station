import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Timing {
    private List<Trip> tripList;
    

    public Timing() {
        this.tripList = new ArrayList<>();
    }

    public void addTrip(Trip trip) {
        try {
            if (trip == null) {
                throw new IllegalArgumentException("Trip cannot be null!");
            }
            
            this.tripList.add(trip);
            System.out.println("Trip added to schedule: " + trip.getRoute());
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error adding trip: " + e.getMessage());
            throw e;
        }
    }

    public void displayAllTrips() {
        System.out.println("=== All trips (" + this.tripList.size() + ") ===");
        if (this.tripList.isEmpty()) {
            System.out.println("Schedule is empty");
        } else {
            for (Trip trip : this.tripList) {
                System.out.println("• " + trip.getRoute()
                    + " - " + trip.getStatus()
                    + " (" + trip.getPrice() + " rub.)");
            }
        }
        System.out.println("==========================");
    }

    public void displayActiveTrips() {
        System.out.println("=== Active trips ===");
        int count = 0;
        for (Trip trip : this.tripList) {
            if (trip.getStatus().equals("Planned") || trip.getStatus().equals("In progress")) {
                System.out.println("- " + trip.getRoute()
                    + " - " + trip.getStatus());
                count++;
            }
        }
        if (count == 0) {
            System.out.println("No active trips");
        }
        System.out.println("==========================");
    }

    public void displayCompletedTrips() {
        System.out.println("=== Completed trips ===");
        int count = 0;
        for (Trip trip : this.tripList) {
            if (trip.getStatus().equals("Completed")) {
                System.out.println("- " + trip.getRoute()
                    + " - " + trip.getPrice() + " rub.");
                count++;
            }
        }
        if (count == 0) {
            System.out.println("No completed trips");
        }
        System.out.println("==========================");
    }

    public void displayPlannedTrips() {
        System.out.println("=== Planned trips ===");
        int count = 0;
        for (Trip trip : this.tripList) {
            if (trip.getStatus().equals("Planned")) {
                System.out.println("• " + trip.getRoute()
                    + " - " + trip.getPrice() + " rub.");
                count++;
            }
        }
        if (count == 0) {
            System.out.println("No planned trips");
        }
        System.out.println("==========================");
    }

    public Trip chooseTrip() {
        try {
            this.displayActiveTrips();

            if (this.tripList.isEmpty()) {
                throw new IllegalStateException("No available trips!");
            }

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter trip route: ");
            String selectedRoute = scanner.nextLine();
            
            if (selectedRoute == null || selectedRoute.trim().isEmpty()) {
                throw new IllegalArgumentException("Route cannot be empty!");
            }

            for (Trip trip : this.tripList) {
                if (trip.getRoute().equals(selectedRoute) &&
                    (trip.getStatus().equals("Planned") || trip.getStatus().equals("In progress"))) {
                    System.out.println(" Selected trip: " + selectedRoute);
                    return trip;
                }
            }

            throw new IllegalStateException("Active trip with route '" + selectedRoute + "' not found!");
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error choosing trip: " + e.getMessage());
            return null;
        }
    }

    
    public boolean removeTrip(String route) {
        try {
            if (route == null || route.trim().isEmpty()) {
                throw new IllegalArgumentException("Route cannot be null or empty!");
            }
            
            // Используем Iterator для безопасного удаления
            java.util.Iterator<Trip> iterator = this.tripList.iterator();
            while (iterator.hasNext()) {
                Trip trip = iterator.next();
                if (trip.getRoute().equals(route)) {
                    // Проверяем, можно ли удалить поездку (только запланированные можно удалять)
                    if ("Planned".equals(trip.getStatus())) {
                        iterator.remove();
                        System.out.println("Trip '" + route + "' removed from schedule.");
                        return true;
                    } else {
                        throw new IllegalStateException("Cannot delete trip '" + route + "' because it's " + trip.getStatus() + ". Only planned trips can be deleted.");
                    }
                }
            }
            
            System.out.println("Trip with route '" + route + "' not found.");
            return false;
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error removing trip: " + e.getMessage());
            throw e;
        }
    }

    // Геттер
    public List<Trip> getTripList() {
        return this.tripList;
    }
}