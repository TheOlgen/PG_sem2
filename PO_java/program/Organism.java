package projekt.program;

public abstract class Organism {
    protected World world;
    protected int x, y;
    protected int strength;
    protected int initiative;
    protected char symbol;
    protected boolean alive;

    public Organism(World world, int x, int y, int initiative, int strength, char symbol) {
        this.world = world;
        this.x = x;
        this.y = y;
        this.initiative = initiative;
        this.strength = strength;
        this.symbol = symbol;
        this.alive = true;
        world.addOrganism(this);
    }

    public void draw() {
        System.out.print('[' + this.symbol + ']');
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setPosition(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void increaseStrength(int additionalStrength) {
        this.strength += additionalStrength;
    }

    public int getInitiative() {
        return initiative;
    }

    public char getSymbol() {
        return symbol;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrenght(int strenght){
        this.strength = strenght;
    }
    public void setOrganismsStrenght(int strength){
        if(strength > this.getStrength()){
            this.setStrenght(strength);
        }
    }
    public boolean isAlive() {
        return alive;
    }

    public boolean isSameSpecies(Organism other) {
        return this.symbol == other.symbol;
    }

    public boolean dodge(Organism attacker, Organism attacked) {
        return false; // Override this method for specific animals that can dodge
    }

    public void die(Organism attacker) {
        alive = false;
        if (this.symbol != ',' && this.symbol != '.') {
            System.out.println(attacker.getName() + " eats " + this.getName());
        }
        world.clearPosition(this.x, this.y);
    }

    public boolean randomizePosition(int[] position) {
        position[0] = (int) (Math.random() * 3) - 1;
        if (position[0] != 0) {
            position[1] = (int) (Math.random() * 3) - 1;
        } else {
            position[1] = Math.random() < 0.5 ? -1 : 1;
        }
        return world.isPositionValid(x + position[0], y + position[1]);
    }

    public void move(int px, int py) {
        world.changePosition(this.x, this.y, px, py);
        this.setPosition(x + px, y + py);
    }

    public abstract void action(char command);
    public abstract boolean collision(Organism attacking);
    public abstract void makeChildren(int x, int y);

    public abstract String getName();
}
