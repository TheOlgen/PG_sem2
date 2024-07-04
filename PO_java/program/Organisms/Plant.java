package projekt.program.Organisms;

import projekt.program.Organism;
import projekt.program.World;

import java.util.Random;

public class Plant extends Organism {
    private final int seedingProbability;
    private static final int INITIATIVE = 0;
    public Plant(World world, int x, int y, int strength, char symbol, int seedingProbability) {
        super(world, x, y, Plant.INITIATIVE, strength, symbol);
        this.seedingProbability = seedingProbability;
    }

    @Override
    public String getName() {
        return "Plant";
    }

    public double getSeedingProbability() {
        return seedingProbability;
    }

    @Override
    public void action(char command) {
        tryToSeed();
    }

    protected boolean tryToSeed() {
        int[] position = new int[2];
        int n = new Random().nextInt(seedingProbability);
        //System.out.println(this.getName()+" "+n);
        if (!this.randomizePosition(position) || n  != 0) {
            return false;
        }
        if (world.isPositionEmpty(x + position[0], y + position[1])) {
            this.createChild(x + position[0], y + position[1]);
            return true;
        }
        return false;
    }

    @Override
    public boolean collision(Organism attacker) {
        this.die(attacker);
        return true;
    }

    @Override
    public void makeChildren(int x, int y) {
        // Do nothing
    }

    public Organism createChild(int x, int y) {
        return null;
    }
}

