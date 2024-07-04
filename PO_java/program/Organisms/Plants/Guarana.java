package projekt.program.Organisms.Plants;

import projekt.program.Organism;
import projekt.program.Organisms.Plant;
import projekt.program.World;

public class Guarana extends Plant {
    private static final int GUARANA_STRENGTH = 0; // Example strength for Guarana
    private static final int GUARANA_SEEDING_PROBABILITY = 10; // Example seeding probability

    public Guarana(World world, int x, int y) {
        super(world, x, y, GUARANA_STRENGTH, '^', GUARANA_SEEDING_PROBABILITY);
        // System.out.println("Creating Guarana");
    }

    @Override
    public String getName() {
        return "Guarana";
    }

    @Override
    public Organism createChild(int x, int y) {
        return new Guarana(this.world, x, y);
    }

    @Override
    public boolean collision(Organism attacker) {
        this.die(attacker);
        attacker.increaseStrength(3); // Assuming `increaseStrength` method exists in the Organism class
        System.out.println(attacker.getName() + " now has strength: " + attacker.getStrength());
        return true;
    }
}

