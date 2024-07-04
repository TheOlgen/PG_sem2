package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

import java.util.Random;

public class Turtle extends Animal {

    private static final int TURTLE_INITIATIVE = 1; // Example value
    private static final int TURTLE_STRENGTH = 2; // Example value

    public Turtle(World world, int x, int y) {
        super(world, x, y, TURTLE_INITIATIVE, TURTLE_STRENGTH, 'T');
        System.out.println("Turtle created");
    }

    @Override
    public String getName() {
        return "Turtle";
    }

    @Override
    protected Organism createChild(int x, int y) {
        return new Turtle(this.world, x, y);
    }

    @Override
    public void action(char command) {
        Random random = new Random();
        if (random.nextInt(4) != 0) { // Turtle moves only 25% of the time
            return;
        }
        int[] move = new int[2];
        if (!randomizePosition(move)) {
            return;
        }
        int newX = this.x + move[0];
        int newY = this.y + move[1];
        if (!world.isPositionEmpty(newX, newY)) {
            if (collision(world.getOrganismAtPosition(newX, newY))) {
                move(move[0], move[1]);
            }
        } else {
            move(move[0], move[1]);
        }
    }

    @Override
    public boolean dodge(Organism attacker, Organism attacked) {
        if (attacker.getStrength() < 5) {
            System.out.println("Turtle defended itself from the attack");
            return true;
        }
        return false;
    }
}

