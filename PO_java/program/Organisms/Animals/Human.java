package projekt.program.Organisms.Animals;

import projekt.program.Organism;
import projekt.program.Organisms.Animal;
import projekt.program.World;

public class Human extends Animal {
    private int normalStrength;
    private int turnCounter;
    private static final int HUMAN_INITIATIVE = 4;
    private static final int HUMAN_STRENGTH = 5;


    public Human(World world, int x, int y) {
        super(world, x, y, HUMAN_INITIATIVE, HUMAN_STRENGTH, '@');
        System.out.println("Creating Human");
        this.normalStrength = HUMAN_STRENGTH;
        turnCounter = 0;
    }

    public int getTurnCounter(){
        return turnCounter;
    }

    @Override
    public String getName() {
        return "Human";
    }

    @Override
    public void action(char command) {
        int[] position = new int[2];
        if (!selectFields(position, command)) {
            return;
        }
        if (strength > normalStrength) {
            strength -= 1;
            System.out.println("Super power is active, current strength: " + strength +
                    ". You will be able to use super power again after round: " + turnCounter);
        }
        if (!world.isPositionEmpty(x + position[0], y + position[1])) {
            if (collision(world.getOrganismAtPosition(x + position[0], y + position[1]))) {
                move(position[0], position[1]);
            }
        } else {
            move(position[0], position[1]);
        }
    }

    @Override
    public void increaseStrength(int additionalStrength) {
        this.strength += additionalStrength;
        this.normalStrength += additionalStrength;
    }

    public boolean selectFields(int[] position, char command) {
        switch (command) {
            case 'a': // Move left
                position[0] = -1;
                position[1] = 0;
                break;

            case 's': // Move down
                position[0] = 0;
                position[1] = 1;
                break;

            case 'd': // Move right
                position[0] = 1;
                position[1] = 0;
                break;

            case 'w': // Move up
                position[0] = 0;
                position[1] = -1;
                break;

            case 'n':
                superPower();
                return false;

            case 'z':
                world.saveToFile();
                return false;

            default:
                return false;
        }
        if (world.isPositionValid(x + position[0], y + position[1])) {
            return true;
        }
        return false;
    }

    public void superPower() {
        if (world.getTurn() < turnCounter) {
            System.out.println("You can't unlock the super power yet");
        } else {
            this.strength += 11;
            this.turnCounter = world.getTurn() + 5;
        }
    }

    @Override
    public Organism createChild(int x, int y) {
        return new Human(this.world, x, y);
        //return null;
    }

    @Override
    public void die(Organism killer) {
        alive = false;
        System.out.println(killer.getName() + " eats " + this.getName());
        world.clearPosition(this.x, this.y);
        world.killHuman();
    }

    public void setHumanStrenght(int strength, int targetTurn){
        this.turnCounter = targetTurn;
        if(strength > this.getStrength()){
            this.setStrenght(strength);
            int tmp = targetTurn - world.getTurn() + 5;
            if(tmp>0){
                this.normalStrength = strength-tmp;
            }
        }
    }
}

