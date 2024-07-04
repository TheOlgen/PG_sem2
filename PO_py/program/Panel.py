import tkinter as tk

from program.Organisms import Animal
from program.Organisms.Animals import Sheep


class Panel(tk.Canvas):
    #def __init__(self, master, height, width, rect_size, *args, **kwargs):
    def __init__(self, master, height, width, rect_size, world, *args, **kwargs):
        super().__init__(master, *args, **kwargs)
        self.width = width
        self.height = height
        self.rect_size = rect_size
        self.world = world
        self.config(width=width * rect_size, height=(10 + height) * rect_size + 10)
        self.draw_world()

    def draw_world(self):
        self.delete("all")
        """
        for i in range(self.height):
            for j in range(self.width):
                organism = self.world.get_organism_at_position(j, i)
                if isinstance(organism, Animal):
                    self.create_oval(
                        j * self.rect_size, i * self.rect_size,
                        (j + 1) * self.rect_size, (i + 1) * self.rect_size,
                        fill=self.get_color_for_organism(organism),
                        outline="black"
                    )

                if isinstance(organism, Plant):
                    self.create_rectangle(
                        j * self.rect_size, i * self.rect_size,
                        (j + 1) * self.rect_size, (i + 1) * self.rect_size,
                        fill="green"
                    )
                    color = self.get_color_for_organism(organism)
                    for k in range(4):
                        dot_x = j * self.rect_size + self.rect_size / 4 + (k % 2) * self.rect_size / 2 - self.rect_size / 8
                        dot_y = i * self.rect_size + self.rect_size / 4 + (k // 2) * self.rect_size / 2 - self.rect_size / 8
                        if isinstance(organism, (DeadlyNightshade, Guarana, Barszcz)):
                            self.create_oval(
                                dot_x, dot_y,
                                dot_x + self.rect_size / 6, dot_y + self.rect_size / 6,
                                fill=color
                            )
                        if isinstance(organism, Dandelion):
                            self.create_line(dot_x, dot_y, dot_x + self.rect_size / 6, dot_y + self.rect_size / 6)
                            self.create_line(dot_x + self.rect_size / 6, dot_y, dot_x, dot_y + self.rect_size / 6)
                            self.create_line(dot_x + self.rect_size / 12, dot_y, dot_x + self.rect_size / 12, dot_y + self.rect_size / 6)
                            self.create_line(dot_x, dot_y + self.rect_size / 12, dot_x + self.rect_size / 6, dot_y + self.rect_size / 12)
    """
        self.create_rectangle(10, 10, self.rect_size * self.width, self.rect_size * self.height, outline="black")
        self.create_rectangle(10, self.rect_size * (self.width + 1), self.rect_size * self.width, self.rect_size * 3, outline="black")
        message = f"Aktualna tura: {self.world.get_turn()}"
        self.create_text(self.rect_size, self.rect_size * (self.width + 2), text=message, anchor=tk.NW)


    def refresh(self):
        self.draw_world()


    def get_color_for_organism(self, organism):
        #if isinstance(organism, Wolf):
            #return "gray"
        if isinstance(organism, Sheep):
            return "white"
"""        elif isinstance(organism, Turtle):
            return "darkgreen"
        elif isinstance(organism, Fox):
            return "orange"
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
"""