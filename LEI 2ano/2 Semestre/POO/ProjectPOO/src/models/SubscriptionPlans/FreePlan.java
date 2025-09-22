package models.SubscriptionPlans;

public class FreePlan extends SubscriptionPlan {

    private static final String PLAN_NAME = "Free";
    private static final double PRICE = 0.0;
    private static final double POINTS_ON_SUBSCRIPTION = 0.0;
    private static final double POINTS_PER_PLAY = 5.0;

    public FreePlan() {
        super(PLAN_NAME, PRICE);
    }

    @Override
    public boolean canCreatePlaylist() {
        return false;
    }

    @Override
    public boolean canCreateLibrary() {
        return false;
    }

    @Override
    public boolean hasPersonalizedPlaylists() {
        return false;
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
