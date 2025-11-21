public class Driver extends Workers {
    private String driverLicense;
    private String lastMedical;
    private String currentDriverTrip;
    

    // конструктор
    public Driver(String surname, String name, String middleName, int salary,
                 String license, String lastMedical, String currentDriverTrip) {
        super(surname, name, middleName, salary, true); 
        
        // Валидация параметров
        if (license == null || license.trim().isEmpty()) {
            throw new IllegalArgumentException("Driver license cannot be null or empty!");
        }
        
        this.driverLicense = license;
        this.lastMedical = lastMedical;
        this.currentDriverTrip = currentDriverTrip;
        
    }

    public boolean checkNeedMedical(String currentDate) {
        try {
            if (currentDate == null || currentDate.trim().isEmpty()) {
                throw new IllegalArgumentException("Current date cannot be null or empty!");
            }
            
            boolean result = (!this.lastMedical.equals(currentDate));
            System.out.println(result ? 
                "Medical examination required. Last: " + this.lastMedical + ", date: " + currentDate : 
                "Medical examination not required.");
            return result;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error checking medical: " + e.getMessage());
            return false;
        }
    }

    public void setTrip(String trip) {
        try {
            if (trip == null || trip.trim().isEmpty()) {
                throw new IllegalArgumentException("Trip description cannot be null or empty!");
            }
            
            this.currentDriverTrip = trip;
            System.out.println("Driver assigned to trip: " + trip);
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error setting trip: " + e.getMessage());
            throw e;
        }
    }

    // Геттеры
    public String getLicense() {
        return this.driverLicense;
    }

    public String getLastMedical() {
        return this.lastMedical;
    }

    public String getDriverCurrentTrip() {
        return this.currentDriverTrip;
    }

    // Сеттеры 
    public void setDriverLicense(String license) {
        if (license == null || license.trim().isEmpty()) {
            throw new IllegalArgumentException("Driver license cannot be null or empty!");
        }
        this.driverLicense = license;
    }

    public void setLastMedical(String lastMedical) {
        this.lastMedical = lastMedical;
    }

    public void setCurrentDriverTrip(String currentDriverTrip) {
        this.currentDriverTrip = currentDriverTrip;
    }
}