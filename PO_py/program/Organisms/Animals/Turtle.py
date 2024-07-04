import random
from program.Organisms.Animal import Animal



class Turtle(Animal):
    TURTLE_INITIATIVE = 1
    TURTLE_STRENGTH = 2

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Turtle.TURTLE_INITIATIVE, Turtle.TURTLE_STRENGTH, 'T')
        print("Turtle created")

    def get_name(self):
        return "Turtle"

    def create_child(self, x, y):
        return Turtle(self.world, x, y)

    def action(self, command):
        if random.randint(0, 3) != 0:  # Turtle moves only 25% of the time
            return

        move = [0, 0]
        if not self.randomize_position(move):
            return

        new_x = self.x + move[0]
        new_y = self.y + move[1]

        if not self.world.is_position_empty(new_x, new_y):
            if self.collision(self.world.get_organism_at_position(new_x, new_y)):
                self.move(move[0], move[1])
        else:
            self.move(move[0], move[1])

    def dodge(self, attacker, attacked):
        if attacker.get_strength() < 5:
            print("Turtle defended itself from the attack")
            return True
        return False
