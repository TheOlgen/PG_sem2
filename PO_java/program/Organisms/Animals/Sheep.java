package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

import java.util.Random;

public class Sheep extends Animal {

    private static final int SHEEP_INITIATIVE = 4; // Example value
    private static final int SHEEP_STRENGTH = 4; // Example value

    public Sheep(World world, int x, int y) {
        super(world, x, y, SHEEP_INITIATIVE, SHEEP_STRENGTH, 'O');
        System.out.println("Sheep created");
    }

    @Override
    public String getName() {
        return "Sheep";
    }

    @Override
    protected Organism createChild(int x, int y) {
        return new Sheep(this.world, x, y);
    }
}

