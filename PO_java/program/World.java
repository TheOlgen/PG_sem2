package projekt.program;

import projekt.program.Organisms.Animals.*;
import projekt.program.Organisms.Plants.*;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class World {
    private int height;
    private int width;
    private char[][] fields;
    private List<Organism> organisms;
    private boolean humanAlive;
    private int turn;
    //private String message;

    public World(int height, int width) {
        this.height = height;
        this.width = width;
        this.fields = new char[height][width];
        this.organisms = new ArrayList<>();
        this.humanAlive = true;
        this.turn = 1;
        this.fillBoard();
    }

    private void fillBoard() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                fields[y][x] = ' ';
            }
        }
    }

    public void executeTurn(char command) {
        if (!humanAlive) {
            return;
        }
        System.out.println(" ");
        this.turn += 1;
        List<Organism> organismsCopy = new ArrayList<>(organisms);
        for (int j = 7; j >= 0; j--) {
            for (Organism organism : organismsCopy) {
                if (organism.getInitiative() == j && organism.isAlive()) {
                    organism.action(command);
                }
            }
        }
    }

    public int getTurn() {
        return turn;
    }

    public void setTurn(int newTurn){
        this.turn = newTurn;
    }

    public int getHeight() {
        return height;
    }

    public int getWidth(){
        return width;
    }
    public boolean isPositionEmpty(int x, int y) {
        return fields[y][x] == ' ';
    }

    public boolean isPositionValid(int x, int y) {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    public Organism getOrganismAtPosition(int x, int y) {
        for (Organism organism : organisms) {
            if (organism.getX() == x && organism.getY() == y) {
                return organism;
            }
        }
        return null;
    }

    public void addOrganism(Organism organism) {
        int x, y;
        Random rand = new Random();
        while (true) {
            x = organism.getX();
            y = organism.getY();
            if (isPositionValid(x, y) && isPositionEmpty(x, y)) {
                placeOrganismAtPosition(x, y, organism);
                break;
            } else {
                organism.setPosition(rand.nextInt(width), rand.nextInt(height));
            }
        }
    }

    private void placeOrganismAtPosition(int x, int y, Organism organism) {
        organisms.add(organism);
        fields[y][x] = organism.getSymbol();
    }

    public void changePosition(int x, int y, int px, int py) {
        char tmp = fields[y][x];
        fields[y][x] = ' ';
        fields[y + py][x + px] = tmp;
    }

    public void clearPosition(int x, int y) {
        Organism organism = getOrganismAtPosition(x, y);
        if (organism != null) {
            organisms.remove(organism);
            fields[y][x] = ' ';
        }
    }

    public void killHuman() {
        this.humanAlive = false;
    }

    public void saveToFile() {
        try (PrintWriter writer = new PrintWriter(new File("slot1.txt"))) {
            writer.println(width + " " + height + " " + turn);
            writer.println(organisms.size());
            for (Organism organism : organisms) {
                if(organism instanceof Human){
                    writer.printf("%s %d %d %d %d%n", organism.getName(), organism.getX(), organism.getY(), ((Human) organism).getTurnCounter(), organism.getStrength());
                }
                else writer.printf("%s %d %d %d%n", organism.getName(), organism.getX(), organism.getY(), organism.getStrength());
            }
        } catch (FileNotFoundException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static World loadFromFile() {
        try (BufferedReader reader = new BufferedReader(new FileReader("slot1.txt"))) {
            String[] firstLine = reader.readLine().split(" ");
            int width = Integer.parseInt(firstLine[0]);
            int height = Integer.parseInt(firstLine[1]);
            int turn = Integer.parseInt(firstLine[2]);

            World world = new World(height, width);
            world.setTurn(turn);

            int numberOfAnimals = Integer.parseInt(reader.readLine());
            for (int i = 0; i < numberOfAnimals; i++) {
                String[] organismData = reader.readLine().split(" ");
                String name = organismData[0];
                int x = Integer.parseInt(organismData[1]);
                int y = Integer.parseInt(organismData[2]);
                int strength = Integer.parseInt(organismData[3]);

                switch (name) {
                    case "Human":
                        int turnCounter = Integer.parseInt(organismData[4]);
                        Human h = new Human(world, x, y);
                        h.setHumanStrenght(strength, turnCounter);
                        break;
                    case "Turtle":
                        Turtle t = new Turtle(world, x, y);
                        t.setOrganismsStrenght(strength);
                        break;
                    case "Fox":
                        Fox fox = new Fox(world, x, y);
                        fox.setOrganismsStrenght(strength);
                        break;
                    case "Sheep":
                        Sheep s = new Sheep(world, x, y);
                        s.setOrganismsStrenght(strength);
                        break;
                    case "Wolf":
                        Wolf wolf = new Wolf(world, x, y);
                        wolf.setOrganismsStrenght(strength);
                        break;
                    case "Antelope":
                        Antelope antelope = new Antelope(world, x, y);
                        antelope.setOrganismsStrenght(strength);
                        break;
                    case "Grass":
                        Grass grass = new Grass(world, x, y);
                        break;
                    case "Dandelion":
                        Dandelion dandelion = new Dandelion(world, x, y);
                        break;
                    case "DeadlyNightshade":
                        DeadlyNightshade deadlyNightshade = new DeadlyNightshade(world, x, y);
                        break;
                    case "Guarana":
                        Guarana guarana = new Guarana(world, x, y);
                        break;
                    case "Barszcz":
                        Barszcz barszcz = new Barszcz(world, x, y);
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown organism type: " + name);
                }
            }
            return world;
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return null;
        }
    }

}
