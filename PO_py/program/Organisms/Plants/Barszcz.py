from program.Organisms.Animals.CyberSheep import CyberSheep
from program.Organisms.Plant import Plant

class Barszcz(Plant):

    BARSZCZ_STRENGTH = 10
    BARSZCZ_SEEDING_PROBABILITY = 10

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Barszcz.BARSZCZ_STRENGTH, '+', Barszcz.BARSZCZ_SEEDING_PROBABILITY)
        self.world.add_barszcz()

    def get_name(self):
        return "Barszcz"

    def create_child(self, x, y):
        return Barszcz(self.world, x, y)

    def action(self, command):
        self.try_to_seed()
        self.kill_around(self.x + 1, self.y + 1)
        self.kill_around(self.x + 1, self.y)
        self.kill_around(self.x + 1, self.y - 1)
        self.kill_around(self.x - 1, self.y + 1)
        self.kill_around(self.x - 1, self.y)
        self.kill_around(self.x - 1, self.y - 1)
        self.kill_around(self.x, self.y + 1)
        self.kill_around(self.x, self.y - 1)

    def kill_around(self, x, y):
        if self.world.is_position_valid(x, y):
            if not self.world.is_position_empty(x, y):
                organism = self.world.get_organism_at_position(x, y)
                if isinstance(organism, CyberSheep):
                    return
                if organism.get_initiative() > 0:
                    organism.die(self)

    def collision(self, attacker):
        self.die(attacker)
        if isinstance(attacker, CyberSheep):
            return True
        print(f"{attacker.get_name()} was poisoned by Barszcz and dies")
        if attacker.get_symbol() == '@':
            self.world.kill_human()
        self.world.clear_position(attacker.get_x(), attacker.get_y())
        return True

    def die(self, attacker):
        self.world.destroy_barszcz()
        self.alive = False
        if self.symbol not in [',', '.']:
            print(f"{attacker.get_name()} eats {self.get_name()}")
        self.world.clear_position(self.x, self.y)

