public class Workers extends People {
    protected int salary;
    protected boolean availability;

    // Конструктор
    public Workers(String surname, String name, String middleName, int salary, boolean available) {
        super(surname, name, middleName, "", "", ""); 
        
        // Валидация 
        if (salary < 0) {
            throw new IllegalArgumentException("Salary cannot be negative!");
        }
        
        this.salary = salary;
        this.availability = available;
        
    }

    // Защищенный метод
    protected void makeSalary(int newSalary) {
        try {
            if (newSalary < 0) {
                throw new IllegalArgumentException("Salary cannot be negative!");
            }
            
            this.salary = newSalary;
            System.out.println("[Workers] Salary set: " + this.salary + " rub.");
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error setting salary: " + e.getMessage());
            throw e;
        }
    }

    // Публичные методы
    public boolean getAvailability() {
        return this.availability;
    }

    public void changeWorkAvailability(boolean avail) {
        this.availability = avail;
        System.out.println("[Workers] Availability changed to: " + (this.availability ? "Available" : "Not available"));
    }

    // Геттеры и сеттеры
    public int getSalary() {
        return this.salary;
    }

    public void setSalary(int salary) {
        try {
            if (salary < 0) {
                throw new IllegalArgumentException("Salary cannot be negative!");
            }
            
            this.salary = salary;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error setting salary: " + e.getMessage());
            throw e;
        }
    }

    public void setAvailability(boolean availability) {
        this.availability = availability;
    }
}