from cs50 import get_float
from math import floor

while True:
    change = get_float("Change: ") * 100
    if change > 0:
        break

coins = 0

coins += floor(change / 25)
change -= floor(change / 25) * 25

coins += floor(change / 10)
change -= floor(change / 10) * 10

coins += floor(change / 5)
change -= floor(change / 5) * 5

coins += floor(change / 1)
change -= floor(change / 1) * 1

print(coins)
