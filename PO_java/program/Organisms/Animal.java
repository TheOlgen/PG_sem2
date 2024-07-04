package projekt.program.Organisms;

import projekt.program.Organism;
import projekt.program.World;

import java.util.Random;

public class Animal extends Organism {

    public Animal(World world, int x, int y, int initiative, int strength, char symbol) {
        super(world, x, y, initiative, strength, symbol);
    }

    @Override
    public void action(char command) {
        int[] position = new int[2];
        if (!randomizePosition(position)) {
            return;
        }
        int newX = getX() + position[0];
        int newY = getY() + position[1];

        if (!world.isPositionEmpty(newX, newY)) {
            if (collision(world.getOrganismAtPosition(newX, newY))) {
                move(position[0], position[1]);
            }
        } else {
            move(position[0], position[1]);
        }
    }

    @Override
    public boolean collision(Organism attacked) {
        if (attacked == null) {
            return true;
        }
        if (isSameSpecies(attacked)) {
            makeChildren(getX(), getY());
            return false;
        }
        if (attacked.getInitiative() == 0) {
            return attacked.collision(this);
        }
        return fight(attacked);
    }

    private boolean fight(Organism attacked) {
        System.out.println(this.getName() + " encounters " + attacked.getName() + ", a bloody fight is about to ensue");
        if (dodge(attacked, this)) {
            return false;
        }
        if (attacked.dodge(this, attacked)) {
            return false;
        }
        if (attacked.getStrength() > this.strength) {
            die(attacked);
            return false;
        } else {
            attacked.die(this);
        }
        return true;
    }

    @Override
    public void makeChildren(int x, int y) {
        int[] position = new int[2];
        int attempts = 0;
        while (!randomizePosition(position) || !world.isPositionEmpty(x + position[0], y + position[1])) {
            attempts++;
            if (attempts == 6) {
                position[0] = 0;
                position[1] = 0;
                break;
            }
        }
        System.out.println(this.getName() + " gives birth to a child");
        Organism child = createChild(x + position[0], y + position[1]);
        if (child != null) {
            world.addOrganism(child);
        }
    }

    protected Organism createChild(int x, int y) {
        // Override this method in specific animal subclasses to create a child organism
        return null;
    }

    @Override
    public String getName() {
        return "Animal"; // Override this in specific animal subclasses
    }
}
