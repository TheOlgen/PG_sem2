package projekt;

import projekt.program.MyFrame;
import projekt.program.Organisms.Animals.*;
import projekt.program.Organisms.Plants.*;
import projekt.program.World;

import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        System.out.println("1. New Simulation");
        System.out.println("2. Load Simulation");

        if(scanner.nextInt() == 1){
            int height, width;

            System.out.println("Enter height and width");
            height = scanner.nextInt();
            width = scanner.nextInt();

            World swiat = new World(height, width);

            Human human = new Human(swiat, 1, 1);
            Sheep sheep = new Sheep(swiat, 1, 1);
            Sheep sheep2 = new Sheep(swiat, 1, 1);
            Sheep sheep3 = new Sheep(swiat, 1, 1);
            Sheep sheep4 = new Sheep(swiat, 1, 1);
            Turtle turtle = new Turtle(swiat, 1, 1);
            Turtle turtle1 = new Turtle(swiat, 1, 1);
            Turtle turtle2 = new Turtle(swiat, 1, 1);
            Fox fox = new Fox(swiat, 1,1);
            Fox fox2 = new Fox(swiat, 1,1);
            Wolf wolf = new Wolf(swiat, 1,1);
            Wolf wolf2 = new Wolf(swiat, 1,1);
            Wolf wolf3 = new Wolf(swiat, 1,1);
            Wolf wolf4 = new Wolf(swiat, 1,1);
            //Wolf wolf6 = new Wolf(swiat, 1,1);
            Antelope anty = new Antelope(swiat, 1,1);
            Antelope anty2 = new Antelope(swiat, 1,1);
            Antelope anty3 = new Antelope(swiat, 1,1);
            Grass grass = new Grass(swiat, 1, 1);
            Dandelion dandelion = new Dandelion(swiat, 1,1);
            DeadlyNightshade dedly = new DeadlyNightshade(swiat, 1,1);
            Guarana guarana = new Guarana(swiat, 1,1);
            Barszcz barszcz = new Barszcz(swiat, 1,1);
            new MyFrame(height, width, swiat);
        }
        else{
            World world = World.loadFromFile();
            new MyFrame(world.getHeight(), world.getWidth(), world);
        }
    }
}