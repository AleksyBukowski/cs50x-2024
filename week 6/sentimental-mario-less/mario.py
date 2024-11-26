from cs50 import get_int

while True:
    h = get_int("Height: ")
    if (h > 0 and h <= 8):
        break


for x in range(1, h+1):
    for y in range(h-x):
        print(" ", end="")
    for z in range(x):
        print("#", end="")
    print()
