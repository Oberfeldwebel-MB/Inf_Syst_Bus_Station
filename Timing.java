import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Timing {
    private List<Trip> tripList;

    public Timing() {
        this.tripList = new ArrayList<>();
    }

    public void addTrip(Trip trip) {
        tripList.add(trip);
        System.out.println("Trip added to schedule: " + trip.getRoute());
    }

    public void displayAllTrips() {
        System.out.println("=== All trips (" + tripList.size() + ") ===");
        if (tripList.isEmpty()) {
            System.out.println("Schedule is empty");
        } else {
            for (Trip trip : tripList) {
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
        for (Trip trip : tripList) {
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
        for (Trip trip : tripList) {
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
        for (Trip trip : tripList) {
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
        displayActiveTrips();

        if (tripList.isEmpty()) {
            System.out.println("No available trips!");
            return null;
        }

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter trip route: ");
        String selectedRoute = scanner.nextLine();

        for (Trip trip : tripList) {
            if (trip.getRoute().equals(selectedRoute) &&
                (trip.getStatus().equals("Planned") || trip.getStatus().equals("In progress"))) {
                System.out.println(" Selected trip: " + selectedRoute);
                return trip;
            }
        }

        System.out.println("Active trip with route '" + selectedRoute + "' not found!");
        return null;
    }

    // Getters
    public List<Trip> getTripList() {
        return tripList;
    }
}