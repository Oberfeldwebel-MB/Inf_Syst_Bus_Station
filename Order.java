import java.util.ArrayList;
import java.util.List;

public class Order {
    private List<Ticket> ticketList;
    private String payStatus;
    private double totalPrice;
    private TicketChose ticketChose;
    private Search search;

    public Order(TicketChose chose) {
        this.ticketChose = chose;
        this.ticketList = new ArrayList<>();
        this.payStatus = "Unpaid";
        this.totalPrice = 0.0;
    }

    private void calculateTotalPrice() {
        totalPrice = 0;
        for (Ticket ticket : ticketList) {
            totalPrice += ticket.getPrice();
        }
    }

    public void printOrderInfo() {
        System.out.println("=== Order Information ===");
        System.out.println("Payment status: " + payStatus);
        System.out.println("Total price: " + totalPrice);
        System.out.println("Tickets in order:");
        for (Ticket ticket : ticketList) {
            ticket.printTicketInfo();
        }
        System.out.println("========================");
    }

    public void addTicket(Ticket ticket) {
        ticketList.add(ticket);
        calculateTotalPrice();
        System.out.println("Ticket added to order");
    }

    public boolean removeTicket(Ticket ticket) {
        boolean removed = ticketList.remove(ticket);
        if (removed) {
            calculateTotalPrice();
            System.out.println("Ticket removed from order");
        }
        return removed;
    }

    public void payOrder() {
        payStatus = "Paid";
        System.out.println("Order paid successfully");
    }

    public void cancelOrder() {
        ticketList.clear();
        payStatus = "Cancelled";
        totalPrice = 0.0;
        System.out.println("Order cancelled");
    }

    // Геттеры
    public List<Ticket> getTicketList() {
        return ticketList;
    }

    public String getPayStatus() {
        return payStatus;
    }

    public double getTotalPrice() {
        return totalPrice;
    }

    public boolean isEmpty() {
        return ticketList.isEmpty();
    }
}