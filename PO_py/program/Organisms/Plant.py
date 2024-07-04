from program.Organism import Organism
import random


class Plant(Organism):

    def __init__(self, world, x, y, strength, symbol, seeding_probability):
        super().__init__(world, x, y, 0, strength, symbol)
        self.seeding_probability = seeding_probability

    def get_name(self):
        return "Plant"

    def get_seeding_probability(self):
        return self.seeding_probability

    def action(self, command):
        self.try_to_seed()

    def try_to_seed(self):
        position = [0, 0]
        n = random.randint(0, self.seeding_probability - 1)

        if not self.randomize_position(position) or n != 0:
            return False

        new_x = self.x + position[0]
        new_y = self.y + position[1]

        if self.world.is_position_empty(new_x, new_y):
            self.create_child(new_x, new_y)
            return True

        return False

    def collision(self, attacker):
        self.die(attacker)
        return True

    def make_children(self, x, y):
        pass

    def create_child(self, x, y):
        return None
