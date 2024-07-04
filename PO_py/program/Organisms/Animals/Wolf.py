from program.Organisms.Animal import Animal


class Wolf(Animal):
    Wolf_INITIATIVE = 5
    Wolf_STRENGTH = 9

    def __init__(self, world, x, y):
        super().__init__(world, x, y, self.Wolf_INITIATIVE, self.Wolf_STRENGTH, 'O')
        print("Wolf created")

    def get_name(self):
        return "Wolf"

    def create_child(self, x, y):
        return Wolf(self.world, x, y)
