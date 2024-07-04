from program.Organisms.Plant import Plant


class Grass(Plant):

    GRASS_STRENGTH = 0
    GRASS_SEEDING_PROBABILITY = 4

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Grass.GRASS_STRENGTH, ',', Grass.GRASS_SEEDING_PROBABILITY)

    def get_name(self):
        return "Grass"

    def create_child(self, x, y):
        return Grass(self.world, x, y)
