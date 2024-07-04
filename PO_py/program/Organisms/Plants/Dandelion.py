from program.Organisms.Plant import Plant


class Dandelion(Plant):

    DANDELION_STRENGTH = 0
    DANDELION_SEEDING_PROBABILITY = 5

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Dandelion.DANDELION_STRENGTH, '.', Dandelion.DANDELION_SEEDING_PROBABILITY)

    def get_name(self):
        return "Dandelion"

    def create_child(self, x, y):
        return Dandelion(self.world, x, y)

    def action(self, command):
        self.try_to_seed()
        self.try_to_seed()
        self.try_to_seed()
