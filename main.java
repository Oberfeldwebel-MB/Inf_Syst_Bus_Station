import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        // 1. Статическая инициализация объектов
        System.out.println("1. Static object initialization:");
        System.out.println("----------------------------------------");

        Bus staticBus = new Bus("Mercedes", "Sprinter", 25, "BUS001", "Good", "2024-01-15");
        Driver staticDriver = new Driver("Klevakin", "Yaroslav", "Maximovich", 85000, "D123456", "2024-01-10", "");
        Passenger staticPassenger = new Passenger("Ivanov", "Ivan", "Ivanovich", "1234", "567890", "ivanov@mail.ru");

        System.out.println("Created static objects:");
        staticBus.printBusInfo();
        System.out.println("Driver: " + staticDriver.getFullName());
        System.out.println("Passenger: " + staticPassenger.getFullName() + "\n");

        // 2. Работа с объектами 
        System.out.println("--------------------------------------------");

        Bus dynamicBus = new Bus("Volvo", "Intercity", 40, "BUS002", "Good", "2024-01-20");
        Driver dynamicDriver = new Driver("Strukov", "Ruslan", "Vladimirovich", 50000, "D654321", "2024-01-12", "");
        Admin dynamicAdmin = new Admin("Rumyantsev", "Maxim", "Stanislavovich", 60000);

        System.out.println("Created objects:");
        dynamicBus.printBusInfo();
        System.out.println("Driver: " + dynamicDriver.getFullName());
        System.out.println("Admin: " + dynamicAdmin.getFullName() + "\n");

        // 3. Работа с ссылками
        System.out.println("-----------------------------------");

        Bus busRef = dynamicBus;
        Driver driverRef = dynamicDriver;

        System.out.println("Working with references:");
        System.out.println("- Bus via reference: " + busRef.getModel());
        System.out.println("- Driver via reference: " + driverRef.getLicense() + "\n");

        // 4. Массив объектов класса
        System.out.println("4. Array of class objects:");
        System.out.println("---------------------------------------");

        Bus[] busArray = {
            new Bus("MAN", "Lion", 35, "BUS101", "Good", "2024-01-18"),
            new Bus("Scania", "Interlink", 45, "BUS102", "Good", "2024-01-19")
        };

        System.out.println("Bus array:");
        for (int i = 0; i < busArray.length; i++) {
            System.out.println("- " + busArray[i].getBrand() + " [" + busArray[i].getCode() + "]");
        }
        System.out.println();

        // 5. Массив объектов класса
        System.out.println("5. Array of driver objects:");
        System.out.println("---------------------------------------");

        Driver[] driverArray = {
            new Driver("Ganyushkin", "Konstantin", "Vladimirovich", 48000, "D111111", "2024-01-11", ""),
            new Driver("Valyaev", "Fedor", "Sergeevich", 52000, "D222222", "2024-01-13", "")
        };

        System.out.println("Driver array:");
        for (int i = 0; i < driverArray.length; i++) {
            System.out.println("- " + driverArray[i].getFullName() + " (" + driverArray[i].getLicense() + ")");
        }
        System.out.println();


        // Демонстрация работы системы
        System.out.println("6. SYSTEM DEMONSTRATION:");
        System.out.println("---------------------------------");
        
        // Создаем расписание
        Timing timing = new Timing();
        
        // Создаем автобусы и водителей для демонстрации
        Bus demoBus = new Bus("Mercedes", "Tourismo", 50, "BUS999", "Excellent", "2024-01-25");
        Driver demoDriver = new Driver("Petrov", "Alexey", "Ivanovich", 55000, "D999999", "2024-01-20", "");
        
        // Создаем поездку
        Trip demoTrip = new Trip("Moscow", "Saint Petersburg", 1500, demoBus, demoDriver);
        timing.addTrip(demoTrip);
        
        // Показываем все поездки
        timing.displayAllTrips();
        
        // Создаем пользователя
        User user = new User("Sidorov", "Dmitry", "Petrovich", 
                           "4321", "987654", "sidorov@mail.ru", timing);
        
        System.out.println("User created: " + user.getFullName());
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("\nPress Enter to exit...");
        scanner.nextLine();
    }
}