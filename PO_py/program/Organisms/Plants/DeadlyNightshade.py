from program.Organisms.Plant import Plant


class DeadlyNightshade(Plant):

    NIGHTSHADE_STRENGTH = 99
    NIGHTSHADE_SEEDING_PROBABILITY = 10

    def __init__(self, world, x, y):
        super().__init__(world, x, y, DeadlyNightshade.NIGHTSHADE_STRENGTH, '*', DeadlyNightshade.NIGHTSHADE_SEEDING_PROBABILITY)

    def get_name(self):
        return "DeadlyNightshade"

    def create_child(self, x, y):
        return DeadlyNightshade(self.world, x, y)

    def collision(self, attacker):
        self.die(attacker)
        print(attacker.get_name() + " was poisoned by the berries and dies")
        if attacker.get_symbol() == '@':
            self.world.kill_human()
        self.world.clear_position(attacker.get_x(), attacker.get_y())
        return True
