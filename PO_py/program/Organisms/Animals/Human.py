from program.Organisms.Animal import Animal


class Human(Animal):

    HUMAN_INITIATIVE = 4
    HUMAN_STRENGTH = 5

    def __init__(self, world, x, y):
        super().__init__(world, x, y, Human.HUMAN_INITIATIVE, Human.HUMAN_STRENGTH, '@')
        print("Creating Human")
        self.normal_strength = Human.HUMAN_STRENGTH
        self.turn_counter = 0

    def get_turn_counter(self):
        return self.turn_counter

    def get_name(self):
        return "Human"

    def action(self, command):
        position = [0, 0]
        if not self.select_fields(position, command):
            return

        if self.strength > self.normal_strength:
            self.strength -= 1
            print(f"Super power is active, current strength: {self.strength}. "
                  f"You will be able to use super power again after round: {self.turn_counter}")

        if not self.world.is_position_empty(self.x + position[0], self.y + position[1]):
            if self.collision(self.world.get_organism_at_position(self.x + position[0], self.y + position[1])):
                self.move(position[0], position[1])
        else:
            self.move(position[0], position[1])

    def increase_strength(self, additional_strength):
        self.strength += additional_strength
        self.normal_strength += additional_strength

    def select_fields(self, position, command):
        if command == 'a':  # Move left
            position[0] = -1
            position[1] = 0
        elif command == 's':  # Move down
            position[0] = 0
            position[1] = 1
        elif command == 'd':  # Move right
            position[0] = 1
            position[1] = 0
        elif command == 'w':  # Move up
            position[0] = 0
            position[1] = -1
        elif command == 'n':  # Use superpower
            self.super_power()
            return False
        elif command == 'z':  # Save simulation
            self.world.save_to_file()
            return False
        elif command == 'm':
            self.world.make_barszcz(1,1)
        else:
            return False

        if self.world.is_position_valid(self.x + position[0], self.y + position[1]):
            return True
        return False

    def super_power(self):
        if self.world.get_turn() < self.turn_counter:
            print("You can't unlock the super power yet")
        else:
            self.strength += 11
            self.turn_counter = self.world.get_turn() + 5

    def create_child(self, x, y):
        return Human(self.world, x, y)

    def die(self, killer):
        self.alive = False
        print(f"{killer.get_name()} eats {self.get_name()}")
        self.world.clear_position(self.x, self.y)
        self.world.kill_human()

    def set_human_strength(self, strength, target_turn):
        self.turn_counter = target_turn
        if strength > self.get_strength():
            self.set_strength(strength)
            tmp = target_turn - self.world.get_turn() + 5
            if tmp > 0:
                self.normal_strength = strength - tmp
