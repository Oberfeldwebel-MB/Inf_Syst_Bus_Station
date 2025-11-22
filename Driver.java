public class Driver extends Workers {
    private String driverLicense;
    private String lastMedical;
    private String currentDriverTrip;

    // конструктор
    public Driver(String surname, String name, String middleName, int salary,
                 String license, String lastMedical, String currentDriverTrip) {
        super(surname, name, middleName, salary, true); 
        this.driverLicense = license;
        this.lastMedical = lastMedical;
        this.currentDriverTrip = currentDriverTrip;
    }

    public boolean checkNeedMedical(String currentDate) {
        boolean result = (!lastMedical.equals(currentDate));
        System.out.println(result ? "Medical examination required. Last: " + lastMedical + ", date: " + currentDate : "Medical examination not required.");
        return result;
    }

    public void setTrip(String trip) {
        currentDriverTrip = trip;
        System.out.println("Driver assigned to trip: " + trip);
    }

    // Геттеры
    public String getLicense() {
        return driverLicense;
    }

    public String getLastMedical() {
        return lastMedical;
    }

    public String getDriverCurrentTrip() {
        return currentDriverTrip;
    }

    // Сеттеры
    public void setDriverLicense(String license) {
        driverLicense = license;
    }

    public void setLastMedical(String lastMedical) {
        this.lastMedical = lastMedical;
    }

    public void setCurrentDriverTrip(String currentDriverTrip) {
        this.currentDriverTrip = currentDriverTrip;
    }
}