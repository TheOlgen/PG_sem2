from program.Organisms.Animal import Animal


class Sheep(Animal):
    SHEEP_INITIATIVE = 4  # Example value
    SHEEP_STRENGTH = 4  # Example value

    def __init__(self, world, x, y):
        super().__init__(world, x, y, self.SHEEP_INITIATIVE, self.SHEEP_STRENGTH, 'O')
        print("Sheep created")

    def get_name(self):
        return "Sheep"

    def create_child(self, x, y):
        return Sheep(self.world, x, y)
