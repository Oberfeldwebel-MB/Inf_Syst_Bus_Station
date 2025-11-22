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
        this.surname = surname;
        this.name = name;
        this.middleName = middleName;
        this.passportSeries = passportSeries;
        this.passportNumber = passportNumber;
        this.email = email;
    }

    // Публичные методы класса
    public void printInfo() {
        System.out.println("[People] Full name: " + surname + " " + name + " " + middleName
                + "\nPassport: " + passportSeries + " " + passportNumber
                + "\nEmail: " + email + "\n");
    }

    public String getFullName() {
        return surname + " " + name + " " + middleName;
    }

    // Геттеры
    public String getSurname() {
        return surname;
    }

    public String getName() {
        return name;
    }

    public String getMiddleName() {
        return middleName;
    }

    public String getPassportSeries() {
        return passportSeries;
    }

    public String getPassportNumber() {
        return passportNumber;
    }

    public String getEmail() {
        return email;
    }

    // Сеттеры
    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setName(String name) {
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