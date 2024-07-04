package projekt.program.Organisms.Plants;

import projekt.program.Organism;
import projekt.program.Organisms.Plant;
import projekt.program.World;

public class DeadlyNightshade extends Plant {
    private static final int NIGHTSHADE_STRENGTH = 99;
    private static final int NIGHTSHADE_SEEDING_PROBABILITY = 10; // Example probability

    public DeadlyNightshade(World world, int x, int y) {
        super(world, x, y, NIGHTSHADE_STRENGTH, '*', NIGHTSHADE_SEEDING_PROBABILITY);
        // System.out.println("Creating Deadly Nightshade");
    }

    @Override
    public String getName() {
        return "DeadlyNightshade";
    }

    @Override
    public Organism createChild(int x, int y) {
        return new DeadlyNightshade(this.world, x, y);
    }

    @Override
    public boolean collision(Organism attacker) {
        this.die(attacker);
        System.out.println(attacker.getName() + " was poisoned by the berries and dies");
        if (attacker.getSymbol() == '@') {
            world.killHuman();
        }
        world.clearPosition(attacker.getX(), attacker.getY());
        return true;
    }
}

