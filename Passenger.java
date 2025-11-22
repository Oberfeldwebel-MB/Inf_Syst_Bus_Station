public class Passenger extends People {
    private String passportSeries;
    private String passportNumber;
    private String email;

    public Passenger(String surname, String name, String middleName,
                    String passportSeries, String passportNumber, String email) {
        super(surname, name, middleName, passportSeries, passportNumber, email);
        this.passportSeries = passportSeries;
        this.passportNumber = passportNumber;
        this.email = email;
    }

    // Геттеры для данных пассажира
    public String getPassportSeries() {
        return passportSeries;
    }

    public String getPassportNumber() {
        return passportNumber;
    }

    public String getEmail() {
        return email;
    }

    public void printPassengerInfo() {
        System.out.println("=== Passenger Information ===");
        System.out.println("Full name: " + getFullName());
        System.out.println("Passport: " + passportSeries + " " + passportNumber);
        System.out.println("Email: " + email);
        System.out.println("=============================");
    }
}