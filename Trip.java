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
        this.startPoint = start;
        this.finishPoint = finish;
        this.priceTicket = price;
        this.busData = bus;
        this.driverData = driver;
        this.statusTrip = "Planned"; // Статус по умолчанию
    }

    // Публичные методы 
    public void startTrip() {
        statusTrip = "In progress";
        System.out.println("Trip started: " + startPoint + " - " + finishPoint);
        System.out.println("Driver: " + driverData.getFullName());
        System.out.println("Bus: " + busData.getBrand() + " [" + busData.getCode() + "]");
    }

    public void completeTrip() {
        statusTrip = "Completed";
        System.out.println("Trip completed: " + startPoint + " - " + finishPoint);
    }

    public void cancelTrip() {
        statusTrip = "Cancelled";
        System.out.println("Trip cancelled: " + startPoint + " - " + finishPoint);
    }

    public void printTripInfo() {
        System.out.println("=== Trip Information ===");
        System.out.println("Route: " + startPoint + " → " + finishPoint);
        System.out.println("Status: " + statusTrip);
        System.out.println("Ticket price: " + priceTicket + " rub.");
        if (busData != null) {
            System.out.println("Bus: " + busData.getBrand() + " [" + busData.getCode() + "]");
        } else {
            System.out.println("Bus: not assigned");
        }
        if (driverData != null) {
            System.out.println("Driver: " + driverData.getFullName());
        } else {
            System.out.println("Driver: not assigned");
        }
        System.out.println("=========================");
    }

    public void changeDriver(DriverList driverList) {
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
            System.out.println("No available drivers!");
            return;
        }

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter driver full name: ");
        String selectedName = scanner.nextLine();

        // Поиск и установка водителя
        Driver foundDriver = driverList.findDriverByName(selectedName);
        if (foundDriver != null && foundDriver.getAvailability()) {
            driverData = foundDriver;
            System.out.println("Driver changed to: " + foundDriver.getFullName());

            // Автоматически меняем статус водителя на "занят"
            foundDriver.changeWorkAvailability(false);
        } else {
            System.out.println("Driver not found or unavailable!");
        }
    }

    public void changeBus(BusList busList) {
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
            System.out.println("No available buses!");
            return;
        }

        // Выбор автобуса
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter bus code: ");
        String selectedCode = scanner.nextLine();

        // Поиск и установка автобуса
        Bus foundBus = busList.findBusByCode(selectedCode);
        if (foundBus != null && foundBus.getAvailability()) {
            busData = foundBus;
            System.out.println("Bus changed to: " + foundBus.getBrand()
                + " [" + foundBus.getCode() + "]");

            // Изменение статуса автобуса на "недоступен"
            foundBus.changeAvailBus(false);
        } else {
            System.out.println("Bus not found or unavailable!");
        }
    }

    // Геттеры
    public String getRoute() {
        return startPoint + " - " + finishPoint;
    }

    public String getStatus() {
        return statusTrip;
    }

    public int getPrice() {
        return priceTicket;
    }

    public Bus getBus() {
        return busData;
    }

    public Driver getDriver() {
        return driverData;
    }

    // Сеттеры
    public void setStartPoint(String startPoint) {
        this.startPoint = startPoint;
    }

    public void setFinishPoint(String finishPoint) {
        this.finishPoint = finishPoint;
    }

    public void setStatusTrip(String statusTrip) {
        this.statusTrip = statusTrip;
    }

    public void setPriceTicket(int priceTicket) {
        this.priceTicket = priceTicket;
    }

    public void setBusData(Bus busData) {
        this.busData = busData;
    }

    public void setDriverData(Driver driverData) {
        this.driverData = driverData;
    }
}