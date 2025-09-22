package models.SubscriptionPlans;

public class PremiumTop extends SubscriptionPlan {

    private static final String PLAN_NAME = "Premium Top";
    private static final double PRICE = 19.99;
    private static final double POINTS_ON_SUBSCRIPTION = 100.0;
    private static final double POINTS_PER_PLAY_MULTIPLIER = 0.025;

    public PremiumTop() {
        super(PLAN_NAME, PRICE);
    }

    @Override
    public boolean canCreatePlaylist() {
        return true;
    }

    @Override
    public boolean canCreateLibrary() {
        return true;
    }

    @Override
    public boolean hasPersonalizedPlaylists() {
        return true;
    }

    @Override
    public double getMembershipBonus() {
        return POINTS_ON_SUBSCRIPTION;
    }

    @Override
    public double calculatePlayPoints(double currentPoints) {
        return currentPoints * POINTS_PER_PLAY_MULTIPLIER;
    }
}
