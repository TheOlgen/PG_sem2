import random

from program.Organisms.Animals.Antelope import Antelope
from program.Organisms.Animals.CyberSheep import CyberSheep
from program.Organisms.Animals.Fox import Fox
from program.Organisms.Animals.Human import Human
from program.Organisms.Animals.Sheep import Sheep
from program.Organisms.Animals.Turtle import Turtle
from program.Organisms.Animals.Wolf import Wolf
from program.Organisms.Plants.Barszcz import Barszcz
from program.Organisms.Plants.Dandelion import Dandelion
from program.Organisms.Plants.DeadlyNightshade import DeadlyNightshade
from program.Organisms.Plants.Grass import Grass
from program.Organisms.Plants.Guarana import Guarana


class World:
    def __init__(self, height, width):
        self.height = height
        self.width = width
        self.fields = [[' ' for _ in range(width)] for _ in range(height)]
        self.organisms = []
        self.humanAlive = True
        self.turn = 1
        self.barszcz_num = 0;
        self.fill_board()


    def fill_board(self):
        for y in range(self.height):
            for x in range(self.width):
                self.fields[y][x] = ' '

    def execute_turn(self, command):
        if not self.humanAlive:
            return
        print(" ")
        self.turn += 1
        organisms_copy = self.organisms[:]
        for j in range(7, -1, -1):
            for organism in organisms_copy:
                if organism.get_initiative() == j and organism.is_alive():
                    organism.action(command)

    def get_turn(self):
        return self.turn

    def set_turn(self, new_turn):
        self.turn = new_turn

    def get_height(self):
        return self.height

    def get_width(self):
        return self.width

    def is_position_empty(self, x, y):
        return self.fields[y][x] == ' '

    def is_position_valid(self, x, y):
        return 0 <= x < self.width and 0 <= y < self.height

    def add_barszcz(self):
        self.barszcz_num += 1

    def destroy_barszcz(self):
        self.barszcz_num -=1

    def znajdz_najblizszy_barszcz(self, x, y):
        min_distance = float('inf')
        closest_barszcz = None

        for organism in self.organisms:
            if isinstance(organism, Barszcz):
                distance = abs(organism.x - x) + abs(organism.y - y)
                if distance < min_distance:
                    min_distance = distance
                    closest_barszcz = (organism.x, organism.y)

        return closest_barszcz

    def get_organism_at_position(self, x, y):
        for organism in self.organisms:
            if organism.get_x() == x and organism.get_y() == y:
                return organism
        return None

    def add_organism(self, organism):
        while True:
            x = organism.get_x()
            y = organism.get_y()
            if self.is_position_valid(x, y) and self.is_position_empty(x, y):
                self.place_organism_at_position(x, y, organism)
                break
            else:
                organism.set_position(random.randint(0, self.width-1), random.randint(0, self.height-1))

    def place_organism_at_position(self, x, y, organism):
        self.organisms.append(organism)
        self.fields[y][x] = organism.get_symbol()

    def change_position(self, x, y, px, py):
        tmp = self.fields[y][x]
        self.fields[y][x] = ' '
        self.fields[y + py][x + px] = tmp

    def clear_position(self, x, y):
        organism = self.get_organism_at_position(x, y)
        if organism:
            self.organisms.remove(organism)
            self.fields[y][x] = ' '

    def kill_human(self):
        self.humanAlive = False

    def save_to_file(self, filename="slot1.txt"):
        try:
            with open(filename, "w") as file:
                file.write(f"{self.width} {self.height} {self.turn}\n")
                file.write(f"{len(self.organisms)}\n")
                for organism in self.organisms:
                    if isinstance(organism, Human):
                        file.write(f"{organism.get_name()} {organism.get_x()} {organism.get_y()} {organism.get_turn_counter()} {organism.get_strength()}\n")
                    else:
                        file.write(f"{organism.get_name()} {organism.get_x()} {organism.get_y()} {organism.get_strength()}\n")
            print("simulation saved to file 'slot1.txt'")
        except Exception as e:
            print(f"Error saving to file: {e}")

    @staticmethod
    def load_from_file(filename="slot1.txt"):
        try:
            with open(filename, "r") as file:
                lines = file.readlines()
                first_line = lines[0].strip().split(" ")
                width = int(first_line[0])
                height = int(first_line[1])
                turn = int(first_line[2])

                world = World(height, width)
                world.set_turn(turn)

                number_of_animals = int(lines[1].strip())
                for i in range(2, 2 + number_of_animals):
                    organism_data = lines[i].strip().split(" ")
                    name = organism_data[0]
                    x = int(organism_data[1])
                    y = int(organism_data[2])
                    strength = int(organism_data[3])

                    if name == "Human":
                        turn_counter = int(organism_data[4])
                        human = Human(world, x, y)
                        human.set_human_strength(strength, turn_counter)
                    elif name == "Turtle":
                        turtle = Turtle(world, x, y)
                        turtle.set_organism_strength(strength)
                    elif name == "Fox":
                        fox = Fox(world, x, y)
                        fox.set_organism_strength(strength)
                    elif name == "Sheep":
                        sheep = Sheep(world, x, y)
                        sheep.set_organism_strength(strength)
                    elif name == "CyberSheep":
                        sheep = CyberSheep(world, x, y)
                        sheep.set_organism_strength(strength)
                    elif name == "Wolf":
                        wolf = Wolf(world, x, y)
                        wolf.set_organism_strength(strength)
                    elif name == "Antelope":
                        antelope = Antelope(world, x, y)
                        antelope.set_organism_strength(strength)
                    elif name == "Grass":
                        grass = Grass(world, x, y)
                    elif name == "Dandelion":
                        dandelion = Dandelion(world, x, y)
                    elif name == "DeadlyNightshade":
                        deadly_nightshade = DeadlyNightshade(world, x, y)
                    elif name == "Guarana":
                        guarana = Guarana(world, x, y)
                    elif name == "Barszcz":
                        barszcz = Barszcz(world, x, y)
                    else:
                        raise ValueError(f"Unknown organism type: {name}")

                return world
        except Exception as e:
            print(f"Error reading file: {e}")
            return None

    def new_simulation_setup(self):
        Human(self, 1, 1)
        Sheep(self, 1, 1)
        Sheep(self, 1, 1)
        Sheep(self, 1, 1)
        CyberSheep(self, 1, 1)
        Turtle(self, 1, 1)
        Turtle(self, 1, 1)
        Turtle(self, 1, 1)
        Fox(self, 1, 1)
        Fox(self, 1, 1)
        Wolf(self, 1, 1)
        Wolf(self, 1, 1)
        Wolf(self, 1, 1)
        Wolf(self, 1, 1)
        Antelope(self, 1, 1)
        Antelope(self, 1, 1)
        Antelope(self, 1, 1)
        Grass(self, 1, 1)
        Dandelion(self, 1, 1)
        DeadlyNightshade(self, 1, 1)
        Guarana(self, 1, 1)
        Barszcz(self, 1, 1)

    def make_barszcz(self, x, y):
        Barszcz(self, x, y)