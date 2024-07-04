from program.Organisms.Plant import Plant


class Guarana(Plant):

    GUARANA_STRENGTH = 0
    GUARANA_SEEDING_PROBABILITY = 10

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Guarana.GUARANA_STRENGTH, '^', Guarana.GUARANA_SEEDING_PROBABILITY)

    def get_name(self):
        return "Guarana"

    def create_child(self, x, y):
        return Guarana(self.world, x, y)

    def collision(self, attacker):
        self.die(attacker)
        attacker.increase_strength(3)  # Assuming `increase_strength` method exists in the Organism class
        print(f"{attacker.get_name()} now has strength: {attacker.get_strength()}")
        return True
