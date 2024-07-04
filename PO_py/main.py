import random
import sys

from program.World import World
from program.MyFrame import MyFrame

def main():
    print("1. New Simulation")
    print("2. Load Simulation")

    choice = int(input())

    if choice == 1:
        height = int(input("Enter height: "))
        width = int(input("Enter width: "))

        world = World(height, width)
        world.new_simulation_setup()

        frame = MyFrame(height, width, world)
        frame.mainloop()
    else:
        world = World.load_from_file()
        if world:
            frame = MyFrame(world.get_height(), world.get_width(), world)
            frame.mainloop()
        else:
            print("Failed to load the world from file.")

if __name__ == "__main__":
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
