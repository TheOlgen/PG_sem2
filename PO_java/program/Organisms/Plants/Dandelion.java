package projekt.program.Organisms.Plants;

import projekt.program.Organism;
import projekt.program.Organisms.Plant;
import projekt.program.World;

public class Dandelion extends Plant {
    private static final int DANDELION_STRENGTH = 0;
    private static final int DANDELION_SEEDING_PROBABILITY = 5; // Example probability

    public Dandelion(World world, int x, int y) {
        super(world, x, y, DANDELION_STRENGTH, '.', DANDELION_SEEDING_PROBABILITY);
        // System.out.println("Creating Dandelion");
    }

    @Override
    public String getName() {
        return "Dandelion";
    }

    @Override
    public Organism createChild(int x, int y) {
        return new Dandelion(this.world, x, y);
    }

    @Override
    public void action(char command) {
        tryToSeed();
        tryToSeed();
        tryToSeed();
    }
}
