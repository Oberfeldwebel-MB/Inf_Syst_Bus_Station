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
        
        // Валидаци параметров
        if (brand == null || brand.trim().isEmpty()) {
            throw new IllegalArgumentException("Brand cannot be null or empty!");
        }
        if (model == null || model.trim().isEmpty()) {
            throw new IllegalArgumentException("Model cannot be null or empty!");
        }
        if (code == null || code.trim().isEmpty()) {
            throw new IllegalArgumentException("Bus code cannot be null or empty!");
        }
        if (placeCount <= 0) {
            throw new IllegalArgumentException("Seat count must be positive!");
        }
        
        this.brand = brand;
        this.model = model;
        this.placeCount = placeCount;
        this.codeBus = code;
        this.techCondition = techCondition;
        this.lastCheckTO = lastCheck;
    }

    // Методы класса
    public boolean checkAvailBus() {
        return this.busAvailability;
    }

    public void changeAvailBus(boolean state) {
        this.busAvailability = state;
        System.out.println(state ? "Bus is now available" : "Bus is now unavailable");
    }

    public void setTripBus() {
        System.out.println("Bus " + this.codeBus + 
            (this.busAvailability ? " assigned to a trip." : " is not available for a trip."));
    }

    public void goToTO(String date) {
        try {
            if (date == null || date.trim().isEmpty()) {
                throw new IllegalArgumentException("Maintenance date cannot be null or empty!");
            }
            
            this.lastCheckTO = date;
            this.techCondition = "In maintenance";
            this.busAvailability = false;
            System.out.println("Bus " + this.codeBus + " sent to maintenance on " + date + ".");
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error sending bus to maintenance: " + e.getMessage());
            throw e;
        }
    }

    public void changeCondition(String newState) {
        try {
            if (newState == null || newState.trim().isEmpty()) {
                throw new IllegalArgumentException("Technical condition cannot be null or empty!");
            }
            
            this.techCondition = newState;
            System.out.println("Bus " + this.codeBus + " technical condition updated to: " + newState);
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error changing condition: " + e.getMessage());
            throw e;
        }
    }

    public void printBusInfo() {
        System.out.println("=== Bus Data ===");
        System.out.println("Brand: " + this.brand);
        System.out.println("Model: " + this.model);
        System.out.println("Seat count: " + this.placeCount);
        System.out.println("Bus code: " + this.codeBus);
        System.out.println("Technical condition: " + this.techCondition);
        System.out.println("Last maintenance: " + this.lastCheckTO);
        System.out.println("Status: " + (this.busAvailability ? "Available" : "Not available"));
        System.out.println("=================");
    }

    // Геттеры
    public String getBrand() {
        return this.brand;
    }

    public String getModel() {
        return this.model;
    }

    public int getPlaces() {
        return this.placeCount;
    }

    public boolean getAvailability() {
        return this.busAvailability;
    }

    public String getCode() {
        return this.codeBus;
    }

    public String getTechCondition() {
        return this.techCondition;
    }

    public String getLastCheckTO() {
        return this.lastCheckTO;
    }

    // Сеттеры 
    public void setBrand(String newBrand) {
        if (newBrand == null || newBrand.trim().isEmpty()) {
            throw new IllegalArgumentException("Brand cannot be null or empty!");
        }
        this.brand = newBrand;
    }

    public void setModel(String newModel) {
        if (newModel == null || newModel.trim().isEmpty()) {
            throw new IllegalArgumentException("Model cannot be null or empty!");
        }
        this.model = newModel;
    }

    public void setPlaceCount(int count) {
        if (count <= 0) {
            throw new IllegalArgumentException("Seat count must be positive!");
        }
        this.placeCount = count;
    }

    public void setCodeBus(String code) {
        if (code == null || code.trim().isEmpty()) {
            throw new IllegalArgumentException("Bus code cannot be null or empty!");
        }
        this.codeBus = code;
    }

    public void setTechCondition(String condition) {
        this.techCondition = condition;
    }

    public void setLastCheckTO(String lastCheck) {
        this.lastCheckTO = lastCheck;
    }
}