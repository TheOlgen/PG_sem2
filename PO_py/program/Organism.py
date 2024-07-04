import random

class Organism:
    def __init__(self, world, x, y, initiative, strength, symbol):
        self.world = world
        self.x = x
        self.y = y
        self.initiative = initiative
        self.strength = strength
        self.symbol = symbol
        self.alive = True
        world.add_organism(self)

    def draw(self):
        print(f'[{self.symbol}]', end='')

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def set_position(self, x, y):
        self.x = x
        self.y = y

    def increase_strength(self, additional_strength):
        self.strength += additional_strength

    def get_initiative(self):
        return self.initiative

    def set_initiative(self, new_initiative):
        self.initiative = new_initiative

    def get_symbol(self):
        return self.symbol

    def get_strength(self):
        return self.strength

    def set_strength(self, strength):
        self.strength = strength

    def set_organism_strength(self, strength):
        if strength > self.get_strength():
            self.set_strength(strength)

    def is_alive(self):
        return self.alive

    def is_same_species(self, other):
        return self.symbol == other.symbol

    def dodge(self, attacker, attacked):
        return False  # Override this method for specific animals that can dodge

    def die(self, attacker):
        self.alive = False
        if self.symbol not in [',', '.']:
            print(f"{attacker.get_name()} eats {self.get_name()}")
        self.world.clear_position(self.x, self.y)

    def randomize_position(self, position):
        position[0] = random.randint(-1, 1)
        if position[0] != 0:
            position[1] = random.randint(-1, 1)
        else:
            position[1] = -1 if random.random() < 0.5 else 1
        return self.world.is_position_valid(self.x + position[0], self.y + position[1])

    def move(self, px, py):
        self.world.change_position(self.x, self.y, px, py)
        self.set_position(self.x + px, self.y + py)

    def action(self, command):
        raise NotImplementedError("Subclasses should implement this method")

    def collision(self, attacking):
        raise NotImplementedError("Subclasses should implement this method")

    def make_children(self, x, y):
        raise NotImplementedError("Subclasses should implement this method")

    def get_name(self):
        raise NotImplementedError("Subclasses should implement this method")
