public class Passenger extends People {
    private String passportSeries;
    private String passportNumber;
    private String email;
    

    public Passenger(String surname, String name, String middleName,
                    String passportSeries, String passportNumber, String email) {
        super(surname, name, middleName, passportSeries, passportNumber, email);
        
        // Валидация параметров
        if (passportSeries == null || passportSeries.trim().isEmpty()) {
            throw new IllegalArgumentException("Passport series cannot be null or empty!");
        }
        if (passportNumber == null || passportNumber.trim().isEmpty()) {
            throw new IllegalArgumentException("Passport number cannot be null or empty!");
        }
        if (email == null || email.trim().isEmpty()) {
            throw new IllegalArgumentException("Email cannot be null or empty!");
        }
        
        this.passportSeries = passportSeries;
        this.passportNumber = passportNumber;
        this.email = email;
    }
    

    // Геттеры 
    public String getPassportSeries() {
        return this.passportSeries;
    }

    public String getPassportNumber() {
        return this.passportNumber;
    }

    public String getEmail() {
        return this.email;
    }

    public void printPassengerInfo() {
        System.out.println("=== Passenger Information ===");
        System.out.println("Full name: " + this.getFullName());
        System.out.println("Passport: " + this.passportSeries + " " + this.passportNumber);
        System.out.println("Email: " + this.email);
        System.out.println("=============================");
    }
    
    // Сеттеры 
    public void setPassportSeries(String passportSeries) {
        if (passportSeries == null || passportSeries.trim().isEmpty()) {
            throw new IllegalArgumentException("Passport series cannot be null or empty!");
        }
        this.passportSeries = passportSeries;
    }
    
    public void setPassportNumber(String passportNumber) {
        if (passportNumber == null || passportNumber.trim().isEmpty()) {
            throw new IllegalArgumentException("Passport number cannot be null or empty!");
        }
        this.passportNumber = passportNumber;
    }
    
    public void setEmail(String email) {
        if (email == null || email.trim().isEmpty()) {
            throw new IllegalArgumentException("Email cannot be null or empty!");
        }
        this.email = email;
    }
}