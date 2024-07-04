from program.Organism import Organism
import random

class Animal(Organism):

    def __init__(self, world, x, y, initiative, strength, symbol):
        super().__init__(world, x, y, initiative, strength, symbol)

    def action(self, command):
        position = [0, 0]
        if not self.randomize_position(position):
            return

        new_x = self.x + position[0]
        new_y = self.y + position[1]

        if not self.world.is_position_empty(new_x, new_y):
            if self.collision(self.world.get_organism_at_position(new_x, new_y)):
                self.move(position[0], position[1])
        else:
            self.move(position[0], position[1])

    def collision(self, attacked):
        if attacked is None:
            return True
        if self.is_same_species(attacked):
            self.make_children(self.x, self.y)
            return False
        if attacked.get_initiative() == 0:
            return attacked.collision(self)
        return self.fight(attacked)

    def fight(self, attacked):
        print(f"{self.get_name()} encounters {attacked.get_name()}, a bloody fight is about to ensue")
        if self.dodge(attacked, self):
            return False
        if attacked.dodge(self, attacked):
            return False
        if attacked.get_strength() > self.strength:
            self.die(attacked)
            return False
        else:
            attacked.die(self)
        return True

    def make_children(self, x, y):
        position = [0, 0]
        attempts = 0
        while not self.randomize_position(position) or not self.world.is_position_empty(x + position[0], y + position[1]):
            attempts += 1
            if attempts == 6:
                position = [0, 0]
                break
        print(f"{self.get_name()} gives birth to a child")
        child = self.create_child(x + position[0], y + position[1])
        if child:
            self.world.add_organism(child)

    def create_child(self, x, y):
        # Override this method in specific animal subclasses to create a child organism
        return None

    def get_name(self):
        return "Animal"  # Override this in specific animal subclasses

    def dodge(self, attacker, attacked):
        # Override this method in specific animal subclasses for dodging behavior
        return False

    def randomize_position(self, move):
        move[0] = random.randint(-1, 1)
        if move[0] != 0:
            move[1] = random.randint(-1, 1)
        else:
            move[1] = -1 if random.random() < 0.5 else 1

        if self.world.is_position_valid(self.x + (move[0] * 2), self.y + (move[1] * 2)):
            move[0] *= 2
            move[1] *= 2
            return True
        elif self.world.is_position_valid(self.x + move[0], self.y + move[1]):
            return True
        return False
