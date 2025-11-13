public class Workers extends People {
    protected int salary;
    protected boolean availability;

    // Конструктор
    public Workers(String surname, String name, String middleName, int salary, boolean available) {
        super(surname, name, middleName, "", "", ""); 
        this.salary = salary;
        this.availability = available;
    }

    // Защищенный метод
    protected void makeSalary(int newSalary) {
        salary = newSalary;
        System.out.println("[Workers] Salary set: " + salary + " rub.");
    }

    // Публичные методы
    public boolean getAvailability() {
        return availability;
    }

    public void changeWorkAvailability(boolean avail) {
        availability = avail;
        System.out.println("[Workers] Availability changed to: " + (availability ? "Available" : "Not available"));
    }

    // Геттеры и сеттеры
    public int getSalary() {
        return salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    public void setAvailability(boolean availability) {
        this.availability = availability;
    }
}