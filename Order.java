import java.util.ArrayList;
import java.util.List;

public class Order {
    private List<Ticket> ticketList;
    private String payStatus;
    private double totalPrice;
    private TicketChose ticketChose;
    private Search search;
    
    

    public Order(TicketChose chose) {
        try {
            if (chose == null) {
                throw new IllegalArgumentException("TicketChose cannot be null!");
            }
            
            this.ticketChose = chose;
            this.ticketList = new ArrayList<>();
            this.payStatus = "Unpaid";
            this.totalPrice = 0.0;
            
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error creating order: " + e.getMessage());
            throw e;
        }
    }
    
    private void calculateTotalPrice() {
        this.totalPrice = 0;
        for (Ticket ticket : this.ticketList) {
            this.totalPrice += ticket.getPrice();
        }
    }

    public void printOrderInfo() {
        System.out.println("=== Order Information ===");
        System.out.println("Payment status: " + this.payStatus);
        System.out.println("Total price: " + this.totalPrice);
        System.out.println("Tickets in order:");
        for (Ticket ticket : this.ticketList) {
            ticket.printTicketInfo();
        }
        System.out.println("========================");
    }

    public void addTicket(Ticket ticket) {
        try {
            if (ticket == null) {
                throw new IllegalArgumentException("Ticket cannot be null!");
            }
            
            // проверка на дублирование билетов с тем же местом
            for (Ticket existingTicket : this.ticketList) {
                if (existingTicket.getPlaceNumber() == ticket.getPlaceNumber()) {
                    throw new IllegalStateException("Ticket for seat " + ticket.getPlaceNumber() + " already exists in order!");
                }
            }
            
            this.ticketList.add(ticket);
            this.calculateTotalPrice();
            System.out.println("Ticket added to order");
            
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.err.println("Error adding ticket: " + e.getMessage());
            throw e;
        }
    }

    public boolean removeTicket(Ticket ticket) {
        try {
            if (ticket == null) {
                throw new IllegalArgumentException("Ticket cannot be null!");
            }
            
            boolean removed = this.ticketList.remove(ticket);
            if (removed) {
                this.calculateTotalPrice();
                System.out.println("Ticket removed from order");
            }
            return removed;
            
        } catch (IllegalArgumentException e) {
            System.err.println("Error removing ticket: " + e.getMessage());
            return false;
        }
    }

    public void payOrder() {
        try {
            if (this.ticketList.isEmpty()) {
                throw new IllegalStateException("Cannot pay empty order!");
            }
            
            if ("Paid".equals(this.payStatus)) {
                throw new IllegalStateException("Order is already paid!");
            }
            
            this.payStatus = "Paid";
            System.out.println("Order paid successfully");
            
        } catch (IllegalStateException e) {
            System.err.println("Error paying order: " + e.getMessage());
            throw e;
        }
    }

    public void cancelOrder() {
        this.ticketList.clear();
        this.payStatus = "Cancelled";
        this.totalPrice = 0.0;
        System.out.println("Order cancelled");
    }

    // Геттеры
    public List<Ticket> getTicketList() {
        return this.ticketList;
    }

    public String getPayStatus() {
        return this.payStatus;
    }

    public double getTotalPrice() {
        return this.totalPrice;
    }

    public boolean isEmpty() {
        return this.ticketList.isEmpty();
    }
    
    // Сеттер 
    public void setSearch(Search search) {
        this.search = search;
    }
}