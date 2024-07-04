import random

from program.Organisms.Animals.Sheep import Sheep


class CyberSheep(Sheep):
    CSHEEP_STRENGTH = 11  # Example value

    def __init__(self, world, x, y):
        super().__init__(world, x, y)
        self.set_strength(self.CSHEEP_STRENGTH)
        print("CyberSheep created")

    def get_name(self):
        return "CyberSheep"

    def create_child(self, x, y):
        return Sheep(self.world, x, y)

    def action(self, command):
        position = [0, 0]
        if self.world.barszcz_num > 0:
            self.go_to_barszcz(position)
        elif not self.randomize_position(position):
            return

        new_x = self.x + position[0]
        new_y = self.y + position[1]

        if not self.world.is_position_empty(new_x, new_y):
            if self.collision(self.world.get_organism_at_position(new_x, new_y)):
                self.move(position[0], position[1])
        else:
            self.move(position[0], position[1])

    def go_to_barszcz(self, position):
        destination = self.world.znajdz_najblizszy_barszcz(self.x, self.y)
        if not destination:
            return  # No Barszcz found, do nothing

        dest_x, dest_y = destination
        dx = dest_x - self.x
        dy = dest_y - self.y

        # Normalize movement to be at most 1 step in any direction
        if dx > 0:
            dx = 1
        elif dx < 0:
            dx = -1
        else:
            dx = 0

        if dy > 0:
            dy = 1
        elif dy < 0:
            dy = -1
        else:
            dy = 0

        position[0] = dx
        position[1] = dy

