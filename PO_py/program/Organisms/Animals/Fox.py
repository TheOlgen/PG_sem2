from program.Organisms.Animal import Animal



class Fox(Animal):
    FOX_INITIATIVE = 7
    FOX_STRENGTH = 3

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Fox.FOX_INITIATIVE, Fox.FOX_STRENGTH, 'F')
        print("Fox created")

    def get_name(self):
        return "Fox"

    def create_child(self, x, y):
        return Fox(self.world, x, y)

    def action(self, command):
        move = [0, 0]
        if not self.randomize_position(move):
            return

        new_x = self.x + move[0]
        new_y = self.y + move[1]

        # Check if the target position is occupied and if the strength of the organism at the position is higher
        if not self.world.is_position_empty(new_x, new_y):
            if self.world.get_organism_at_position(new_x, new_y).get_strength() > self.get_strength():
                return
            if self.collision(self.world.get_organism_at_position(new_x, new_y)):
                self.move(move[0], move[1])
        else:
            self.move(move[0], move[1])
