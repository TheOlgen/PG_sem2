package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

import java.util.Random;

public class Antelope extends Animal {

    private static final int ANTELOPE_INITIATIVE = 4;
    private static final int ANTELOPE_STRENGTH = 4;

    public Antelope(World world, int x, int y) {
        super(world, x, y, ANTELOPE_INITIATIVE, ANTELOPE_STRENGTH, 'A');
        System.out.println("Antelope created");
    }

    @Override
    public String getName() {
        return "Antelope";
    }

    @Override
    protected Organism createChild(int x, int y) {
        return new Antelope(this.world, x, y);
    }

    @Override
    public boolean randomizePosition(int[] move) {
        Random rand = new Random();
        move[0] = rand.nextInt(3) - 1;
        if (move[0] != 0) {
            move[1] = rand.nextInt(3) - 1;
        } else {
            move[1] = (rand.nextBoolean() ? -1 : 1);
        }
        if (world.isPositionValid(x + (move[0] * 2), y + (move[1] * 2))) {
            move[0] *= 2;
            move[1] *= 2;
            return true;
        } else if (world.isPositionValid(x + move[0], y + move[1])) {
            return true;
        }
        return false;
    }

    @Override
    public boolean dodge(Organism attacker, Organism defender) {
        if (defender.getSymbol() == 'A') {
            Random rand = new Random();
            if (rand.nextBoolean()) {
                System.out.println("Antelope avoids the attack");
                int[] move = new int[2];
                defender.randomizePosition(move);
                defender.move(move[0], move[1]);
                return true;
            }
        }
        return false;
    }
}

