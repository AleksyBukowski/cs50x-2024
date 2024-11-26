import cs50

def main():
        meow(cs50.get_int("n: "))

def meow(n):
    for _ in range(n):
        print("meow")

main()

# we have to define a main function in order to make the meow function work, because meow is declared below. we also need to call the main() function so the program runs.
