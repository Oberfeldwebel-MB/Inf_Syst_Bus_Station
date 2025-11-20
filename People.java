public class People {
    protected String surname;
    protected String name;
    protected String middleName;
    protected String passportSeries;
    protected String passportNumber;
    protected String email;

    // Конструктор
    public People(String surname, String name, String middleName, 
                 String passportSeries, String passportNumber, String email) {
        
        // Валидация 
        if (surname == null || surname.trim().isEmpty()) {
            throw new IllegalArgumentException("Surname cannot be null or empty!");
        }
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("Name cannot be null or empty!");
        }
        
        this.surname = surname;
        this.name = name;
        this.middleName = middleName;
        this.passportSeries = passportSeries;
        this.passportNumber = passportNumber;
        this.email = email;
        
    }
    

    // Публичные методы класс
    public void printInfo() {
        System.out.println("[People] Full name: " + this.surname + " " + this.name + " " + this.middleName
                + "\nPassport: " + this.passportSeries + " " + this.passportNumber
                + "\nEmail: " + this.email + "\n");
    }

    public String getFullName() {
        return this.surname + " " + this.name + " " + this.middleName;
    }

    // Геттеры
    public String getSurname() {
        return this.surname;
    }

    public String getName() {
        return this.name;
    }

    public String getMiddleName() {
        return this.middleName;
    }

    public String getPassportSeries() {
        return this.passportSeries;
    }

    public String getPassportNumber() {
        return this.passportNumber;
    }

    public String getEmail() {
        return this.email;
    }

    // Сеттеры 
    public void setSurname(String surname) {
        if (surname == null || surname.trim().isEmpty()) {
            throw new IllegalArgumentException("Surname cannot be null or empty!");
        }
        this.surname = surname;
    }

    public void setName(String name) {
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("Name cannot be null or empty!");
        }
        this.name = name;
    }

    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }

    public void setPassportSeries(String passportSeries) {
        this.passportSeries = passportSeries;
    }

    public void setPassportNumber(String passportNumber) {
        this.passportNumber = passportNumber;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}