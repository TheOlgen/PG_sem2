import random
from program.Organisms.Animal import Animal

class Antelope(Animal):

    ANTELOPE_INITIATIVE = 4
    ANTELOPE_STRENGTH = 4

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Antelope.ANTELOPE_INITIATIVE, Antelope.ANTELOPE_STRENGTH, 'A')
        print("Antelope created")

    def get_name(self):
        return "Antelope"

    def create_child(self, x, y):
        return Antelope(self.world, x, y)

    def randomize_position(self, move):
        rand = random.Random()
        move[0] = rand.randint(-1, 1)
        if move[0] == 0:
            move[1] = -1 if rand.random() < 0.5 else 1
        else:
            move[1] = rand.randint(-1, 1)
        if self.world.is_position_valid(self.x + (move[0] * 2), self.y + (move[1] * 2)):
            move[0] *= 2
            move[1] *= 2
            return True
        elif self.world.is_position_valid(self.x + move[0], self.y + move[1]):
            return True
        return False

    def dodge(self, attacker, defender):
        if defender.get_symbol() == 'A':
            rand = random.Random()
            if rand.random() < 0.5:  # 50% chance to dodge the attack
                print("Antelope avoids the attack")
                move = [0, 0]
                self.randomize_position(move)
                self.move(move[0], move[1])
                return True
        return False
