import tkinter as tk

# Import klas Animal i Sheep
from program.Organisms.Animal import Animal
from program.Organisms.Animals.Antelope import Antelope
from program.Organisms.Animals.CyberSheep import CyberSheep
from program.Organisms.Animals.Fox import Fox
from program.Organisms.Animals.Human import Human
from program.Organisms.Animals.Turtle import Turtle
from program.Organisms.Animals.Wolf import Wolf
from program.Organisms.Animals.Sheep import Sheep
from program.Organisms.Plant import Plant
from program.Organisms.Plants.Barszcz import Barszcz
from program.Organisms.Plants.Dandelion import Dandelion
from program.Organisms.Plants.DeadlyNightshade import DeadlyNightshade
from program.Organisms.Plants.Guarana import Guarana
from program.Panel import Panel


class MyFrame(tk.Tk):
    RECT_SIZE = 30
    LOCATION = 40
    DISPLACE = 10

    #def __init__(self, height, width):
    def __init__(self, height, width, world):
        super().__init__()
        self.title("Olga Rodziewicz s198421 gr4")
        self.world = world
        self.height = height
        self.width = width
        self.geometry(f"{(width + 5) * self.RECT_SIZE}x{(height + 8) * self.RECT_SIZE}+{self.LOCATION}+{self.LOCATION}")

        self.canvas = tk.Canvas(self, width=width * self.RECT_SIZE + self.DISPLACE, height=height * self.RECT_SIZE + self.DISPLACE*7)
        self.canvas.pack()

        self.create_buttons()
        self.draw_world()


    def create_buttons(self):
        button_frame = tk.Frame(self)
        button_frame.pack()
        buttons = [
            ("Go left", 'a'),
            ("Go up", 'w'),
            ("Go down", 's'),
            ("Go right", 'd'),
            ("Use superpower", 'n'),
            ("Save simulation", 'z'),
            ("Make new Barszcz", 'm')
        ]
        for text, command in buttons:
            button = tk.Button(button_frame, text=text, command=lambda c=command: self.new_turn(c))
            button.pack(side=tk.LEFT)


    def new_turn(self, command):
        self.world.execute_turn(command)
        self.refresh()


    def draw_world(self):
        self.canvas.delete("all")

        for i in range(self.height):
            for j in range(self.width):
                organism = self.world.get_organism_at_position(j, i)
                if isinstance(organism, Animal):
                    self.canvas.create_oval(
                        j * self.RECT_SIZE + self.DISPLACE, i * self.RECT_SIZE + self.DISPLACE,
                        (j + 1) * self.RECT_SIZE + self.DISPLACE, (i + 1) * self.RECT_SIZE + self.DISPLACE,
                        fill=self.get_color_for_organism(organism),
                        outline="black"
                    )
                    if isinstance(organism, CyberSheep) and self.world.barszcz_num>0:
                        self.canvas.create_text(j * self.RECT_SIZE + self.DISPLACE*2.5, i * self.RECT_SIZE + self.DISPLACE*2.5, text="C")

                if isinstance(organism, Plant):
                    self.canvas.create_rectangle(
                        j * self.RECT_SIZE + self.DISPLACE, i * self.RECT_SIZE+ self.DISPLACE,
                        (j + 1) * self.RECT_SIZE+ self.DISPLACE, (i + 1) * self.RECT_SIZE+ self.DISPLACE,
                        fill="green",
                        outline= "green"
                    )
                    color = self.get_color_for_organism(organism)
                    for k in range(4):
                        dot_x = j * self.RECT_SIZE + self.RECT_SIZE / 4 + (k % 2) * self.RECT_SIZE / 2 - self.RECT_SIZE / 8 + self.DISPLACE
                        dot_y = i * self.RECT_SIZE + self.RECT_SIZE / 4 + (k // 2) * self.RECT_SIZE / 2 - self.RECT_SIZE / 8 + self.DISPLACE
                        if isinstance(organism, (DeadlyNightshade, Guarana, Barszcz)):
                            self.canvas.create_oval(
                                dot_x, dot_y,
                                dot_x + self.RECT_SIZE / 6, dot_y + self.RECT_SIZE / 6,
                                fill=color,
                                outline = color
                            )
                        if isinstance(organism, Dandelion):
                            self.canvas.create_line(dot_x, dot_y, dot_x + self.RECT_SIZE / 6, dot_y + self.RECT_SIZE / 6, fill=color)
                            self.canvas.create_line(dot_x + self.RECT_SIZE / 6, dot_y, dot_x, dot_y + self.RECT_SIZE / 6, fill=color)
                            self.canvas.create_line(dot_x + self.RECT_SIZE / 12, dot_y, dot_x + self.RECT_SIZE / 12, dot_y + self.RECT_SIZE / 6, fill=color)
                            self.canvas.create_line(dot_x, dot_y + self.RECT_SIZE / 12, dot_x + self.RECT_SIZE / 6, dot_y + self.RECT_SIZE / 12, fill=color)

        self.canvas.create_rectangle(10, 10, self.RECT_SIZE * self.width + 10, self.RECT_SIZE * self.height + 10, outline="black")
        message = f"Aktualna tura: {self.world.get_turn()}"
        self.canvas.create_text(self.RECT_SIZE + 10, self.RECT_SIZE * (self.width + 1), text=message, anchor=tk.NW)


    def refresh(self):
        self.draw_world()

    def get_color_for_organism(self, organism):
        if isinstance(organism, Wolf):
            return "gray"
        if isinstance(organism, Sheep):
            return "white"
        elif isinstance(organism, Fox):
            return "orange"
        elif isinstance(organism, Turtle):
            return "darkgreen"
        elif isinstance(organism, Antelope):
            return "yellow"
        elif isinstance(organism, Human):
            return "pink"
        elif isinstance(organism, Guarana):
            return "red"
        elif isinstance(organism, Dandelion):
            return "yellow"
        elif isinstance(organism, DeadlyNightshade):
            return "magenta"
        elif isinstance(organism, Barszcz):
            return "white"
        return "black"

