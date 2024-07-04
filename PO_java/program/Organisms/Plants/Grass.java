package projekt.program.Organisms.Plants;

import projekt.program.Organism;
import projekt.program.Organisms.Plant;
import projekt.program.World;

public class Grass extends Plant {
    private static final int GRASS_STRENGTH = 0;
    private static final int GRASS_SEEDING_PROBABILITY = 4; // Example probability

    public Grass(World world, int x, int y) {
        super(world, x, y, GRASS_STRENGTH, ',', GRASS_SEEDING_PROBABILITY);
        // System.out.println("Creating Grass");
    }

    @Override
    public String getName() {
        return "Grass";
    }

    @Override
    public Organism createChild(int x, int y) {
        return new Grass(this.world, x, y);
    }
}

