package models.SubscriptionPlans;

import java.io.Serializable;

public abstract class SubscriptionPlan implements Serializable {
    private final String planName;
    private final double price;
    
    public SubscriptionPlan(String planName, double price) {
        this.planName = planName;
        this.price = price;
    }

    // Basic methods
    public String getPlanName() {
        return planName;
    }

    public double getPrice() {
        return price;
    }

    // Feature control
    public abstract boolean canCreatePlaylist();
    public abstract boolean canCreateLibrary();
    public abstract boolean hasPersonalizedPlaylists();
    
    // Points system
    public abstract double getMembershipBonus();
    public abstract double calculatePlayPoints(double currentPoints); // Add parameter
}
