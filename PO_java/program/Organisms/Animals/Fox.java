package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

import java.util.Random;

public class Fox extends Animal {

    private static final int FOX_INITIATIVE = 7;
    private static final int FOX_STRENGTH = 3;

    public Fox(World world, int x, int y) {
        super(world, x, y, FOX_INITIATIVE, FOX_STRENGTH, 'F');
        System.out.println("Fox created");
    }

    @Override
    public String getName() {
        return "Fox";
    }

    @Override
    protected Organism createChild(int x, int y) {
        return new Fox(this.world, x, y);
    }

    @Override
    public void action(char command) {
        int[] move = new int[2];
        if (!randomizePosition(move)) {
            return;
        }
        int newX = this.x + move[0];
        int newY = this.y + move[1];

        // Check if the target position is occupied and if the strength of the organism at the position is higher
        if (!world.isPositionEmpty(newX, newY)) {
            if (world.getOrganismAtPosition(newX, newY).getStrength() > this.getStrength()) {
                return;
            }
            if (collision(world.getOrganismAtPosition(newX, newY))) {
                move(move[0], move[1]);
            }
        } else {
            move(move[0], move[1]);
        }
    }
}
