package models.SubscriptionPlans;

public class PremiumBase extends SubscriptionPlan {

    private static final String PLAN_NAME = "Premium Base";
    private static final double PRICE = 9.99;
    private static final double POINTS_ON_SUBSCRIPTION = 50.0;
    private static final double POINTS_PER_PLAY = 10.0;

    public PremiumBase() {
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
        return POINTS_PER_PLAY;
    }
}
