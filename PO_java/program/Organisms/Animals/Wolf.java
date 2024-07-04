package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

import java.util.Random;

public class Wolf extends Animal {

    private static final int WOLF_INITIATIVE = 5; // Example value, set according to your game's rules
    private static final int WOLF_STRENGTH = 9;  // Example value, set according to your game's rules

    public Wolf(World world, int x, int y) {
        super(world, x, y, WOLF_INITIATIVE, WOLF_STRENGTH, 'W');
        System.out.println("Wolf created");
    }

    @Override
    public String getName() {
        return "Wolf";
    }

    @Override
    protected Organism createChild(int x, int y) {
        return new Wolf(this.world, x, y);
    }
}

