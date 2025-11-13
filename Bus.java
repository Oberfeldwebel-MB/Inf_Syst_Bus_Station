public class Bus {
    private String brand;
    private String model;
    private int placeCount = 0;
    private boolean busAvailability = true;
    private String codeBus;
    private String techCondition;
    private String lastCheckTO;


    public Bus(String brand, String model, int placeCount, String code, 
               String techCondition, String lastCheck) {
        this.brand = brand;
        this.model = model;
        this.placeCount = placeCount;
        this.codeBus = code;
        this.techCondition = techCondition;
        this.lastCheckTO = lastCheck;
    }

    // Методы класса
    public boolean checkAvailBus() {
        return busAvailability;
    }

    public void changeAvailBus(boolean state) {
        busAvailability = state;
        if (state) {
            System.out.println("Bus is now available");
        } else {
            System.out.println("Bus is now unavailable");
        }
    }

    public void setTripBus() {
        if (busAvailability) {
            System.out.println("Bus " + codeBus + " assigned to a trip.");
        } else {
            System.out.println("Bus " + codeBus + " is not available for a trip.");
        }
    }

    public void goToTO(String date) {
        lastCheckTO = date;
        techCondition = "In maintenance";
        busAvailability = false;
        System.out.println("Bus " + codeBus + " sent to maintenance on " + date + ".");
    }

    public void changeCondition(String newState) {
        techCondition = newState;
        System.out.println("Bus " + codeBus + " technical condition updated to: " + newState);
    }

    public void printBusInfo() {
        System.out.println("=== Bus Data ===");
        System.out.println("Brand: " + brand);
        System.out.println("Model: " + model);
        System.out.println("Seat count: " + placeCount);
        System.out.println("Bus code: " + codeBus);
        System.out.println("Technical condition: " + techCondition);
        System.out.println("Last maintenance: " + lastCheckTO);
        System.out.println("Status: " + (busAvailability ? "Available" : "Not available"));
        System.out.println("=================");
    }

    // Геттеры
    public String getBrand() {
        return brand;
    }

    public String getModel() {
        return model;
    }

    public int getPlaces() {
        return placeCount;
    }

    public boolean getAvailability() {
        return busAvailability;
    }

    public String getCode() {
        return codeBus;
    }

    public String getTechCondition() {
        return techCondition;
    }

    public String getLastCheckTO() {
        return lastCheckTO;
    }

    // Сеттеры
    public void setBrand(String newBrand) {
        brand = newBrand;
    }

    public void setModel(String newModel) {
        model = newModel;
    }

    public void setPlaceCount(int count) {
        placeCount = count;
    }

    public void setCodeBus(String code) {
        codeBus = code;
    }

    public void setTechCondition(String condition) {
        techCondition = condition;
    }

    public void setLastCheckTO(String lastCheck) {
        lastCheckTO = lastCheck;
    }
}