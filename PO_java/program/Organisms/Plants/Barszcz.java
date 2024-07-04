package projekt.program.Organisms.Plants;

import projekt.program.Organism;
import projekt.program.Organisms.Plant;
import projekt.program.World;

public class Barszcz extends Plant {
    private static final int HOGWEED_STRENGTH = 10; // Example strength
    private static final int HOGWEED_SEEDING_PROBABILITY = 10; // Example seeding probability

    public Barszcz(World world, int x, int y) {
        super(world, x, y, HOGWEED_STRENGTH, '+', HOGWEED_SEEDING_PROBABILITY);
        // System.out.println("Creating Giant Hogweed");
    }

    @Override
    public String getName() {
        return "Barszcz";
    }

    @Override
    public Organism createChild(int x, int y) {
        return new Barszcz(this.world, x, y);
    }

    @Override
    public void action(char command) {
        tryToSeed();
        killAround(x + 1, y + 1);
        killAround(x + 1, y);
        killAround(x + 1, y - 1);
        killAround(x - 1, y + 1);
        killAround(x - 1, y);
        killAround(x - 1, y - 1);
        killAround(x, y + 1);
        killAround(x, y - 1);
    }

    private void killAround(int x, int y) {
        if (world.isPositionValid(x, y)) {
            if (!world.isPositionEmpty(x, y)) {
                if (world.getOrganismAtPosition(x, y).getInitiative() > 0) {
                    world.getOrganismAtPosition(x, y).die(this);
                }
            }
        }
    }

    @Override
    public boolean collision(Organism attacker) {
        this.die(attacker);
        System.out.println(attacker.getName() + " was poisoned by Barszcz and dies");
        if (attacker.getSymbol() == '@') {
            world.killHuman();
        }
        world.clearPosition(attacker.getX(), attacker.getY());
        return true;
    }

}
